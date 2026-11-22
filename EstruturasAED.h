#ifndef ESTRUTURASAED_H
#define ESTRUTURASAED_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class StackNode {
public:
    T data;
    StackNode* next;
    StackNode(T d) : data(d), next(nullptr) {}
};

template <typename T>
class Pilha {
    StackNode<T>* topNode;
    int count;

public:
    Pilha() : topNode(nullptr), count(0) {}

    ~Pilha() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }

    void push(T val) {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    void pop() {
        if (isEmpty()) return;
        StackNode<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    T top() const {
        return topNode->data;
    }

    void displayTop(int limit) const {
        StackNode<T>* curr = topNode;
        int shown = 0;
        while (curr && shown < limit) {
            cout << "  - " << curr->data << "\n";
            curr = curr->next;
            shown++;
        }
        if (shown == 0) cout << "  (Nenhum evento registrado ainda)\n";
    }
};

template <typename T>
class QueueNode {
public:
    T data;
    QueueNode* next;
    QueueNode(T d) : data(d), next(nullptr) {}
};

template <typename T>
class Fila {
    QueueNode<T>* frontNode;
    QueueNode<T>* rearNode;
    int count;

public:
    Fila() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~Fila() {
        while (!isEmpty()) {
            T item = dequeue();
            delete item;
        }
    }

    bool isEmpty() const { return frontNode == nullptr; }
    int size() const { return count; }

    void enqueue(T val) {
        QueueNode<T>* newNode = new QueueNode<T>(val);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) return nullptr;
        QueueNode<T>* temp = frontNode;
        T val = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete temp;
        count--;
        return val;
    }

    T front() const {
        if (isEmpty()) return nullptr;
        return frontNode->data;
    }
};

struct HashEntry {
    string key;
    string info;
    HashEntry* next;
    HashEntry(string k, string i) : key(k), info(i), next(nullptr) {}
};

class TabelaHash {
    static const int TABLE_SIZE = 11;
    HashEntry* table[TABLE_SIZE];

    int hashFunction(string key) const {
        int sum = 0;
        for (size_t i = 0; i < key.length(); i++) {
            sum += key[i];
        }
        return sum % TABLE_SIZE;
    }

public:
    TabelaHash() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }

    ~TabelaHash() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashEntry* curr = table[i];
            while (curr) {
                HashEntry* next = curr->next;
                delete curr;
                curr = next;
            }
        }
    }

    void insert(string key, string info) {
        int idx = hashFunction(key);
        HashEntry* newEntry = new HashEntry(key, info);
        newEntry->next = table[idx];
        table[idx] = newEntry;
    }

    string search(string key) const {
        int idx = hashFunction(key);
        HashEntry* curr = table[idx];
        while (curr) {
            if (curr->key == key) return curr->info;
            curr = curr->next;
        }
        return "Planta nao encontrada no Almanaque.";
    }
};

#endif