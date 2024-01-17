//
// Created by iansg on 1/17/2024.
//

#ifndef ADS_HW2_HASHTABLE_H
#define ADS_HW2_HASHTABLE_H

#include <vector>
using namespace std;

typedef long long ll;

template<typename T, typename U>
class HashTable {
    ll a{};
    int r{};
    int sz{};
    int upper{};
    int lower{};

    int _hash(int k, int m) {

    }

    void _compute_bounds() {

    }

    void _resize(int n) {

    }

public:
    HashTable(int r = 200) : r(r) {}

    HashTable(const vector<T> &other, int r = 200) : r(r) {}

    ~HashTable() {}

    int size() { return sz; }

    struct iterator {

    };

    void build(const vector<T> &other) {

    }

    bool find(int k) {

    }

    bool insert(const pair<T, U> &x) {

    }

    pair<T, U> erase(int k) {

    }

    iterator find_min() {

    }

    iterator find_max() {

    }

    iterator find_next() {

    }

    iterator find_prev() {

    }

    iterator begin() {

    }

    iterator end() {

    }
};

#endif //ADS_HW2_HASHTABLE_H
