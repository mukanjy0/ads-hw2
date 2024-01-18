//
// Created by iansg on 1/17/2024.
//

#ifndef ADS_HW2_SET_H
#define ADS_HW2_SET_H

#include "HashTable.h"

template<typename T>
class Set {
    hash_table<T, T> contenedor;
public:
    Set() = default;
    ~Set(){};
    void insert(T value) {
        contenedor.insert(value, value);
    }
    bool remove(T value) {
        if (!contains(value)) {
            return false;
        }
        contenedor.erase(value);
        return true;
    }
    bool contains(T value) {
        return contenedor.contains(value);
    }
    Set set_union(const Set<T>& other) {
        Set<T> new_set;
        for (auto iter = other.contenedor.begin(); iter != other.contenedor.end(); iter++) {
            new_set.insert(iter.value);
        }
        for (auto iter = this->contenedor.begin(); iter != this->contenedor.end(); iter++) {
            new_set.insert(iter.value);
        }
        return new_set;
    }
    Set set_intersect(const Set<T>& other) {
        Set<T> new_set;
        for (auto iter = other.contenedor.begin(); iter != other.contenedor.end(); iter++) {
            if (contains(iter.value)) {
                new_set.insert(iter.value);
            }
        }
        return new_set;
    }
    Set set_difference(const Set<T>& other) {
        Set<T> new_set;
        for (auto iter = this->contenedor.begin(); iter != this->contenedor.end(); iter++) {
            new_set.insert(iter.value);
        }
        for (auto iter = other.contenedor.begin(); iter != other.contenedor.end(); iter++) {
            if (contains(iter.value)) {
                new_set.remove(iter.value);
            }
        }
        return new_set;
    }

    friend ostream& operator<<(ostream& os, const Set<T>& my_set) {
        for (auto iter = my_set->contenedor.begin(); iter != my_set->contenedor.end(); iter++) {
            os << iter.value << " ";
        }
        return os;
    }
};

#endif //ADS_HW2_SET_H
