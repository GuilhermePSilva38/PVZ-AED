#ifndef LDE_H
#define LDE_H

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LDE {
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LDE() : head(nullptr), tail(nullptr), size(0) {}

    ~LDE() {
        clear();
    }

    void insert(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void removeNode(Node<T>* targetNode) {
        if (!targetNode || !head) return;

        if (targetNode == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (targetNode == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
        } else {
            targetNode->prev->next = targetNode->next;
            targetNode->next->prev = targetNode->prev;
        }

        delete targetNode->data;
        delete targetNode;
        size--;
    }

    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current->data;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    Node<T>* search(T target) {
        Node<T>* current = head;
        while (current) {
            if (current->data == target) return current;
            current = current->next;
        }
        return nullptr;
    }

    void sort(bool (*compare)(T, T)) {
        if (!head || !head->next) return;
        
        bool swapped;
        Node<T>* ptr1;
        Node<T>* lptr = nullptr;
        
        do {
            swapped = false;
            ptr1 = head;
            
            while (ptr1->next != lptr) {
                if (compare(ptr1->data, ptr1->next->data)) {
                    T temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    Node<T>* getHead() const { return head; }
    int getSize() const { return size; }
};

#endif