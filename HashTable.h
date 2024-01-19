//
// Created by iansg on 1/17/2024.
//

#ifndef ADS_HW2_HASHKeyTypeABLE_H
#define ADS_HW2_HASHKeyTypeABLE_H

#include "SinglyLinkedList.h"
#include <functional>
#include <climits>
#include <vector>
using namespace std;

template<typename KeyType, typename ValueType>
class hash_table {
    struct Pair {
        KeyType key {};
        ValueType value {};
        Pair() = default;
        Pair(KeyType key, ValueType value) : key(key), value(value) {}
        friend ostream& operator<<(ostream& out, const Pair& p) {
            out << "{" << p.key << ", " << p.value << "}";
            return out;
        }
    };

    class iterator {
        int index {};
        int capacity {};
        Node<Pair>* data {};
        singly_linked_list<Pair>* ht {};
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = Node<Pair>;
        using pointer = Node<Pair>*;
        using reference = Node<Pair>&;
        using iterator_category = forward_iterator_tag;

        iterator() = default; // end
        iterator(singly_linked_list<Pair>* ht, int capacity) : ht(ht), capacity(capacity) {
            for (int i = 0; i < capacity; i++) {
                if (!ht[i].empty()) {
                    data = ht[i].head;
                    index = i;
                    break;
                }
            }
        } // begin
        iterator(singly_linked_list<Pair>* ht, int capacity, Node<Pair>* data, int index) : ht(ht), capacity(capacity), data(data), index(index) {}
        Pair operator*() {
            if (data == nullptr)
                throw runtime_error("Iterator does not point to a value.");

            return data->value;
        }
        Pair* operator->() {
            return &(data->value);
        }

        iterator operator++()  {
            if (data == nullptr) return *this;

            if (data->next != nullptr) {
                data = data->next;
                return *this;
            }
            index++;
            for (; index < capacity; ++index) {
                if (ht[index].empty()) continue;
                data = ht[index].head;
                return *this;
            }
            data = nullptr;
            return *this;
        }
        iterator operator++(int) {
            if (data == nullptr) return *this;

            iterator old = *this;
            if (data->next != nullptr) {
                data = data->next;
                return old;
            }
            index++;
            for (; index < capacity; ++index) {
                if (ht[index].empty()) continue;
                data = ht[index].head;
                return old;
            }
            data = nullptr;
            return old;
        }
        bool operator==(const iterator& other) {
            return data == other.data;
        }
        bool operator!=(const iterator& other) {
            return !(*this == other);
        }
    };

    int sz {};
    int capacity {4};
    int max_collision {3};
    int resize_factor {2};
    double max_fill_factor {0.5};

    singly_linked_list<Pair>* ht {};

    int _hash(KeyType key) const {
        return hash<KeyType>{}(key) % capacity;
    }

    bool _to_resize() {
        return double(sz) / (capacity * max_collision) > max_fill_factor;
    }

    void _resize() {
        capacity *= resize_factor;
        auto* new_ht = new singly_linked_list<Pair>[capacity];

        for (int i = 0; i < capacity / resize_factor; ++i) {
            while (!ht[i].empty()) {
                auto p = ht[i].pop_front();
                new_ht[_hash(p.key)].push_front(p);
            }
        }

        delete ht;
        ht = new_ht;
    }

public:
    hash_table() {
        ht = new singly_linked_list<Pair>[capacity];
    }

    explicit hash_table(const vector<pair<KeyType, ValueType>> &other) {
        ht = new singly_linked_list<Pair>[capacity];
        build(other);
    }

    ~hash_table() {
        delete ht;
    }

    [[nodiscard]] int size() const { return sz; }
    [[nodiscard]] bool empty() const { return sz == 0; }

    void build(const vector<pair<KeyType, ValueType>> &other) {
        for (const auto& iterator: other) {
            insert(iterator.first, iterator.second);
        }
    }

    iterator begin() const {
        return iterator(ht, capacity);
    }

    iterator end() const {
        return iterator();
    }

    bool contains(KeyType key) {
        int idx = _hash(key);
        for (int i = 0; i < ht[idx].size(); i++) {
            if (key == ht[idx][i].key) {
                return true;
            }
        }
        return false;
    }

    iterator find(KeyType key) const {
        int idx = _hash(key);
        Node<Pair>* temp = ht[idx].head;
        for (int i = 0; i < ht[idx].size(); ++i) {
            if (temp->value.key == key) return iterator(ht, capacity, temp, idx);
            temp = temp->next;
        }

        return end();
    }

    ValueType operator[](KeyType key) const {
        return find(key)->value;
    }

    ValueType& operator[](KeyType key) {
        int idx = _hash(key);
        for (int i = 0; i < ht[idx].size(); i++) {
            if (key == ht[idx][i].key) {
                return ht[idx][i].value;
            }
        }
        throw runtime_error("No existe la llave.");
    }

    bool insert(KeyType key, ValueType value) { // returns false if there was no insertion nor update
        int ind = _hash(key);

        int high = ht[ind].size();
        for (int i = 0; i < high; ++i) {
            if (ht[ind][i].key == key) {
                if (ht[ind][i].value == value) return false;

                ht[ind][i] = Pair(key, value);
                return true;
            }
        }

        ++sz;
        if (_to_resize()) {
            _resize();
            ind = _hash(key);
        }

        ht[ind].push_front(Pair(key, value));
        return true;
    }

    ValueType erase(KeyType key) {
        int ind = _hash(key);
        for (int i = 0; i < ht[ind].size(); ++i) {
            if (ht[ind][i].key == key) {
                return ht[ind].remove(i).value;
            }
        }
        throw runtime_error("Invalid key.");
    }

    iterator find_min() {
        auto min = begin();
        for (auto it = ++begin(); it != end(); ++it) {
            if (min->key > it->key) min = it;
        }

        return min;
    }

    iterator find_max() {
        auto max = begin();
        for (auto it = ++begin(); it != end(); ++it) {
            if (max->key < it->key) max = it;
        }

        return max;
    }

    iterator find_next(KeyType key) { // upper_bound for the key
        auto nxt = end();
        for (auto it = begin(); it != end(); ++it) {
            if (it->key > key) {
                if (nxt == end()) {
                    nxt = it;
                } else {
                    if (nxt->key > it->key) nxt = it;
                }
            }
        }

        return nxt;
    }

    iterator find_prev(KeyType key) { // highest key lower than provided key
        auto prev = end();
        for (auto it = begin(); it != end(); ++it) {
            if (it->key < key) {
                if (prev == end()) {
                    prev = it;
                } else {
                    if (prev->key < it->key) prev = it;
                }
            }
        }

        return prev;
    }

    singly_linked_list<Pair> iter_order() {
        singly_linked_list<Pair> sll;
        auto it = find_min();
        while (it != end()) {
            sll.push_back(*it);
            it = find_next(it->key);
        }
        return sll;
    }

    void clear() {
        sz = 0;
        capacity = 4;
        delete ht;
        ht = new singly_linked_list<Pair>[capacity];
    }

    friend ostream& operator<<(ostream& out, const hash_table& htb) {
        for (int i = 0; i < htb.capacity; ++i)
            out << htb.ht[i];
        return out;
    }
};

#endif //ADS_HW2_HASHKeyTypeABLE_H
