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
    ht.insert('B', 2);
    ht.insert('C', 3);
    ht.insert('D', 3);
    ht.insert('E', 3);
    cout << ht << endl;
    cout << "---" << endl;
    auto iter = ht.begin();
    cout << *iter << endl;
    ++iter;
    cout << *iter << endl;
    ++iter;
    cout << *iter << endl;
    ++iter;
    cout << *iter << endl;
    ++iter;
    cout << *iter << endl;
    ++iter;
    cout << boolalpha << (iter == ht.begin()) << endl;
    cout << boolalpha << (iter != ht.begin()) << endl;
    cout << boolalpha << (iter == ht.end()) << endl;
    cout << boolalpha << (iter != ht.end()) << endl;
    cout << "---" << endl;
    for (auto iter = ht.begin(); iter != ht.end(); ++iter) {
        cout << *iter << endl;
    }
}

void test_postincremento() {
    hash_table<char,int> ht;
    ht.insert('A', 1);
    ht.insert('B', 2);
    ht.insert('C', 3);
    auto iter = ht.begin();
    cout << *(iter++) << endl;
    cout << *iter << endl;

    auto iter2 = ht.begin();
    cout << *(++iter2) << endl;
    cout << *iter2 << endl;
}

void test_set_2() {
    Set<int> my_set_1;
    my_set_1.insert(8);
    my_set_1.insert(9);
    Set<int> my_set_2;
    my_set_2.insert(10);
    my_set_2.insert(11);
    Set<int> union_set = my_set_1.set_union(my_set_2);
    cout << union_set << endl;
    my_set_2.insert(8);
    Set<int> union_inter = my_set_1.set_intersect(my_set_2);
    cout << union_inter << endl;
    Set<int> union_dif1 = my_set_1.set_difference(my_set_2);
    cout << union_dif1 << endl;
    Set<int> union_dif2 = my_set_2.set_difference(my_set_1);
    cout << union_dif2 << endl;
}

int main() {
//    test_build();
//    test_find();
//    test_hash_table_insert_resize();
//    test_erase();
//    test_finds();
//    test_finds_errors();
//    test_set_1();
//    test_begin();
//    test_postincremento();

test_set_2();
    return 0;
}
