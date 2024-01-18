//
// Created by iansg on 1/17/2024.
//

#ifndef ADS_HW2_SINGLYLINKEDLIST_H
#define ADS_HW2_SINGLYLINKEDLIST_H

#include <stdexcept>
#include "HashTable.h"
using namespace std;

template<typename T>
class singly_linked_list ;

template<typename T>
struct Node {
    T value {};
    Node* next {};
    Node() = default;
    explicit Node(T val) : value(val) {}
};

template<typename T>
class singly_linked_list {
    Node<T>* head {};
    int sz {};

    void _reverse(Node<T>* prev, Node<T>* cur) {
        prev->next = nullptr;

        if (cur->next == nullptr) {
            cur->next = prev;
            head = cur;
        }
        else {
            _reverse(cur, cur->next);
            cur->next = prev;
        }
    }

    void _insertion_sort(Node<T>* cur, int c) {
        if (c == 0) return;
        _insertion_sort(cur->next, --c);
        if (cur->value > cur->next->value)
            swap(cur->value, cur->next->value);
    }

public:
    template<typename KeyType, typename ValueType>
    friend class hash_table;
    singly_linked_list() = default;
    singly_linked_list(const singly_linked_list& other) {
        head = other.head;
        sz = other.sz;
    }
    singly_linked_list(singly_linked_list&& other)  noexcept {
        head = std::__exchange(other.head, nullptr);
        sz = std::__exchange(other.sz, 0);
    }
    singly_linked_list& operator=(const singly_linked_list& other) {
        if (this == &other) return *this;

        head = other.head;
        sz = other.sz;

        return *this;
    }
    T front() { return head->value; }
    T back() {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->value;
    }
    void push_front(T val) {
        ++sz;

        Node<T>* node = new Node<T>(val);
        node->next = head;
        head = node;
    }
    void push_back(T val) {
        ++sz;

        if (head == nullptr) {
            head = new Node<T>(val);
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        Node<T>* node = new Node<T>(val);
        temp->next = node;
    }
    T pop_front() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");
        Node<T>* temp = head;
        head = temp->next;

        --sz;

        T el = temp->value;
        delete temp;
        return el;
    }
    T pop_back() {
        if (head == nullptr)
            throw runtime_error("Can't pop when list is empty.");

        --sz;

        if (head->next == nullptr) {
            T el = head->value;
            delete head;
            head = nullptr;
            return el;
        }
        Node<T>* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        T el = temp->next->value;
        delete temp->next;
        temp->next = nullptr;
        return el;
    }
    void insert(T val, int pos) {
        if (pos < 0 || pos > sz)
            throw invalid_argument("Not a valid position.");

        if (pos == 0) {
            push_front(val);
            return;
        }
        if (pos == sz) {
            push_back(val);
            return;
        }

        ++sz;
        Node<T>* temp = head;
        for (int i =  1; i < pos; ++i)
            temp = temp->next;

        Node<T>* node = new Node<T>(val);
        node->next = temp->next;
        temp->next = node;
    }
    T remove(int pos) {
        if (pos < 0 || pos >= sz)
            throw invalid_argument("Not a valid position.");

        if (pos == 0)
            return pop_front();

        if (pos == sz - 1)
            return pop_back();

        --sz;
        Node<T>* temp = head;
        for (int i =  1; i < pos; ++i)
            temp = temp->next;

        Node<T>* aux = temp->next;
        temp->next = temp->next->next;

        T el = aux->value;
        delete aux;
        return el;
    }
    T operator[](int pos) const {
        if (pos >= sz || pos < 0)
            throw invalid_argument("Not a valid index.");
        Node<T>* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;
        return temp->value;
    }
    T& operator[](int pos) {
        if (pos >= sz || pos < 0)
            throw invalid_argument("Not a valid index.");
        Node<T>* temp = head;
        for (int i = 0; i < pos; ++i)
            temp = temp->next;
        return temp->value;
    }
    [[nodiscard]] bool empty() const { return head == nullptr; }
    [[nodiscard]] int size() const { return sz; }
    void clear() {
        if (head == nullptr) return;

        Node<T>* temp;
        while (head->next != nullptr) {
            temp = head;
            head = temp->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }
    // insertion sort
    void sort() {
        for (int i = 0; i < sz; ++i)
            _insertion_sort(head, i);
    }
    void reverse() {
        if (head && head->next)
            _reverse(head, head->next);
    }
    singly_linked_list<T> merge(const singly_linked_list<T>& other) {
        int i {}, j {};
        Node<T>* n1 = head;
        Node<T>* n2 = other.head;
        singly_linked_list<T> result;
        while (i < sz && j < other.sz) {
            if (n1->value > n2->value) {
                result.push_back(n2->value);
                n2 = n2->next;
                ++j;
            }
            else  {
                result.push_back(n1->value);
                n1 = n1->next;
                ++i;
            }
        }
        while (i < sz) {
            result.push_back(n1->value);
            n1 = n1->next;
            ++i;
        }
        while (j < other.sz) {
            result.push_back(n2->value);
            n2 = n2->next;
            ++j;
        }
        return result;
    }
    singly_linked_list<T> intersect(const singly_linked_list& other) {
        int i {}, j {};
        Node<T>* n1 = head;
        Node<T>* n2 = other.head;
        singly_linked_list<T> result;
        while (i < sz && j < other.sz) {
            if (n1->value == n2->value) {
                result.push_back(n1->value);
                n1 = n1->next, n2 = n2->next;
                ++i, ++j;
            }
            else  if (n1->value < n2->value) {
                n1 = n1->next;
                ++i;
            }
            else {
                n2 = n2->next;
                ++j;
            }
        }
        return result;
    }
    friend ostream& operator<<(ostream& out, const singly_linked_list& sll) {
        Node<T>* temp = sll.head;
        if (temp != nullptr) {
            out << temp->value;
            while (temp->next != nullptr) {
                temp = temp->next;
                out << ' ' << temp->value;
            }
        }
        out << '\n';
        return out;
    }
};

#endif //ADS_HW2_SINGLYLINKEDLIST_H
