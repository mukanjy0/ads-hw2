#include <iostream>
#include <random>
#include "HashTable.h"
#include "Set.h"

using namespace std;

void test_hash_table_resize() {
    hash_table<char,int> ht;
//    cout << boolalpha << ht._to_resize();
}

void test_hash_table_insert_resize() {
    hash_table<char,int> ht;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<mt19937::result_type> dist26(0, 25);
    int sz = uniform_int_distribution<int>(0, 100)(rng);
    for (int i = 0; i < sz; ++i) {
        ht.insert(char(97 + dist26(rng)), i);
    }
    cout << ht << ht.size();
}

void test_find() {
    hash_table<char,int> ht;
    ht.insert('A', 1);
    cout << ht['A'] << endl;
    ht['A'] = 2;
    cout << ht['A'] << endl;
    cout << boolalpha << ht.contains('A') << endl;
}

void test_build() {
    vector<pair<char, int>> a;
    a.push_back(make_pair('A', 1));
    a.push_back(make_pair('B', 2));
    hash_table<char,int> ht(a);

    cout << ht << endl;
}

int main() {
    test_build();
//    test_find();
//    test_hash_table_insert_resize();
    return 0;
}
