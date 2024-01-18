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

void test_erase() {
    vector<pair<char, int>> a;
    a.push_back(make_pair('A', 1));
    a.push_back(make_pair('B', 2));
    hash_table<char,int> ht(a);
    ht.erase('C');

    cout << ht << endl;
}

void test_finds() {
    hash_table<char,int> ht;
    ht.insert('A', 1);
    ht.insert('B', 2);
    ht.insert('c', 4);
    ht.insert('d', 4);
    ht.insert('e', 4);
    ht.insert('1', 4);

    cout << "Test find prev\n";
    cout << ht.find_prev('A') << endl;
    cout << ht.find_prev('d') << endl;
    cout << ht.find_prev('c') << endl;

    cout << "Test find next\n";
    cout << ht.find_next('A') << endl;
    cout << ht.find_next('d') << endl;
    cout << ht.find_next('c') << endl;

    cout << "Test find min & max\n";
    cout << ht.find_min() << endl;
    cout << ht.find_max() << endl;
}

void test_finds_errors() {
    hash_table<char,int> ht;
    cout << "Test find min & max\n";
//    cout << ht.find_min() << endl;
//    cout << ht.find_max() << endl;
    ht.insert('A', 1);
    ht.insert('B', 2);
    ht.insert('c', 4);
    ht.insert('d', 4);
    ht.insert('e', 4);
    ht.insert('1', 4);

    cout << "Test find prev\n";
//    cout << ht.find_prev('1') << endl;

    cout << "Test find next\n";
    cout << ht.find_next('e') << endl;

}

void test_set_1() {
    Set<int> my_set;
    my_set.insert(8);
    my_set.insert(8);
    cout << boolalpha << my_set.contains(8) << endl;
    my_set.remove(8);
    cout << boolalpha << my_set.contains(8) << endl;
    my_set.remove(8);
    cout << boolalpha << my_set.contains(8) << endl;

}

void test_begin() {
    hash_table<char,int> ht;
    ht.insert('A', 1);
    auto it = ht.begin();
    cout << *it << '\n';
}

int main() {
//    test_build();
//    test_find();
//    test_hash_table_insert_resize();
//    test_erase();
//    test_finds();
//    test_finds_errors();
//    test_set_1();
    test_begin();
    return 0;
}
