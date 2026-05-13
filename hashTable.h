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

    // H1: primary index table
    HashNode* table[SIZE];

    // H3: fast retrieval cache - recently accessed zones
    GridCell cacheData[5];
    int cacheKeys[5];
    int cacheSize;

public:
    HashTable();

    // hash function: Index = Key mod TableSize
    int hashFunction(int key);

    // H1 operations
    void insert(GridCell val);
    GridCell search(int zone);
    void display();

    // H2: show collision slots (chaining)
    void showCollisions();

    // H3: cache operations
    void updateCache(GridCell val);
    GridCell searchCache(int zone);
    void displayCache();
};

#endif
