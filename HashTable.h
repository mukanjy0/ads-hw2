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
        if (find(key)) {
            
        }
    }

    KeyType find_min() {

    }

    KeyType find_max() {

    }

    KeyType find_next(KeyType key) { // upper_bound for the key

    }

    KeyType find_prev(KeyType key) { // highest key lower than provided key

    }

    friend ostream& operator<<(ostream& out, const hash_table& htb) {
        for (int i = 0; i < htb.capacity; ++i)
            out << htb.ht[i];
        return out;
    }
};

#endif //ADS_HW2_HASHKeyTypeABLE_H
