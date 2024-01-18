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
        iterator() = default; // end
        iterator(singly_linked_list<Pair>* ht, int capacity) : ht(ht), capacity(capacity) {
            for (int i = 0; i < capacity; i++) {
                if (ht[i].empty()) continue;
                data = ht[i].head;
            }
        } // begin
        iterator(singly_linked_list<Pair>* ht, int capacity, Node<Pair>* data) : ht(ht), capacity(capacity), data(data) {}
        Pair operator*() {
            if (data == nullptr)
                throw runtime_error("Iterator does not point to a value.");

            return data->value;
        }

        iterator operator++()  {
            iterator old = *this;
            for (; index < capacity; ++index) {
                if (ht[index].empty()) continue;
            }
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

    void build(const vector<pair<KeyType, ValueType>> &other) {
        for (const auto& iter: other) {
            insert(iter.first, iter.second);
        }
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

    ValueType find(KeyType key) const {
        int idx = _hash(key);
        for (int i = 0; i < ht[idx].size(); i++) {
            if (key == ht[idx][i].key) {
                return ht[idx][i].value;
            }
        }
        throw runtime_error("No existe la llave.");
    }

    ValueType operator[](KeyType key) const {
        return find(key);
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

    KeyType find_min() {
        if (sz == 0)
            throw runtime_error("Can't find min when hash table is empty.");

        bool start = true;
        KeyType mini {};
        for (int i = 0; i < capacity; ++i) {
            for (int j = 0; j < ht[i].size(); ++j) {
                if (start) {
                    mini = ht[i][j].key;
                    start = false;
                }
                else mini = min(mini, ht[i][j].key);
            }
        }
        return mini;
    }

    KeyType find_max() {
        if (sz == 0)
            throw runtime_error("Can't find max when hash table is empty.");

        bool start = true;
        KeyType maxi {};
        for (int i = 0; i < capacity; ++i) {
            for (int j = 0; j < ht[i].size(); ++j) {
                if (start) {
                    maxi = ht[i][j].key;
                    start = false;
                }
                else maxi = max(maxi, ht[i][j].key);
            }
        }
        return maxi;
    }

    KeyType find_next(KeyType key) { // upper_bound for the key
        bool start = true;
        KeyType nxt {};
        for (int i = 0; i < capacity; ++i) {
            for (int j = 0; j < ht[i].size(); ++j) {
                if (ht[i][j].key > key) {
                    if (start) {
                        nxt = ht[i][j].key;
                        start = false;
                    }
                    else nxt = min(nxt, ht[i][j].key);
                }
            }
        }

        if (start)
            throw runtime_error("No greater key exists.");

        return nxt;
    }

    KeyType find_prev(KeyType key) { // highest key lower than provided key
        bool start = true;
        KeyType prev {};
        for (int i = 0; i < capacity; ++i) {
            for (int j = 0; j < ht[i].size(); ++j) {
                if (ht[i][j].key < key) {
                    if (start) {
                        prev = ht[i][j].key;
                        start = false;
                    }
                    else prev = max(prev, ht[i][j].key);
                }
            }
        }

        if (start)
            throw runtime_error("No lower key exists.");

        return prev;
    }

    void clear() {
        sz = 0;
        capacity = 4;
        delete ht;
        ht = new singly_linked_list<Pair>[capacity];
    }

    iterator begin() {
        return iterator(ht, capacity);
    }

    iterator end() {
        return iterator();
    }

    friend ostream& operator<<(ostream& out, const hash_table& htb) {
        for (int i = 0; i < htb.capacity; ++i)
            out << htb.ht[i];
        return out;
    }
};

#endif //ADS_HW2_HASHKeyTypeABLE_H
