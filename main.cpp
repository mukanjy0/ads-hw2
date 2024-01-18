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

int main() {
    cout << boolalpha << (string("hello") < string("helloo")) << '\n';
    test_hash_table_insert_resize();
    return 0;
}
