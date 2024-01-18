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

typedef long long ll;

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

    int _hash(KeyType key) {
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

    hash_table(const vector<KeyType> &other) {}

    ~hash_table() {}

    [[nodiscard]] int size() const { return sz; }

    void build(const vector<KeyType> &other) {

    }

    bool contains(KeyType key) {

    }

    ValueType find(KeyType key) {

    }

    ValueType operator[](KeyType key) const {

    }

    ValueType& operator[](KeyType key) {

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
