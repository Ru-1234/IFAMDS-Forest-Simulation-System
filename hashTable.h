#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"
#include <iostream>
using namespace std;

struct HashNode {
    GridCell data;
    HashNode* next;

    HashNode(GridCell val) {
        data = val;
        next = NULL;
    }
};

class HashTable {
private:
    static const int SIZE = 10;
    HashNode* table[SIZE];

public:
    HashTable();

    int hashFunction(int key);

    void insert(GridCell val);
    GridCell search(int zone);
    void display();
};

#endif