#include "hashTable.h"

// time complexity : o(n) 
HashTable::HashTable() {
    for(int i=0;i<SIZE;i++)
        table[i] = NULL;

    cacheSize = 0;
    for(int i=0;i<5;i++)
        cacheKeys[i] = -1;
}

// ind : key mod TableSize --- Time Complexity: O(1)
int HashTable::hashFunction(int key) {
    return key % SIZE;
}

// H1: insert using zoneID as key, chain on collision
void HashTable::insert(GridCell val) {
    int index = hashFunction(val.zoneID);

    HashNode* nn = new HashNode(val);

    if(table[index] == NULL) {
        table[index] = nn;
    } else {
        HashNode* temp = table[index];
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = nn;
    }

    cout << "H: Inserted Zone!! " << val.zoneID << endl;
}

// Time Complexity: o(n) worst case
GridCell HashTable::search(int zone) {
    int index = hashFunction(zone);

    HashNode* temp = table[index];

    while(temp != NULL) {
        if(temp->data.zoneID == zone) {
            cout << "H: Found Zone " << zone << endl;
            return temp->data;
        }
        temp = temp->next;
    }

    cout << "H: Zone Not Found" << endl;
    return {-1, -1};
}

// Time Complexity: O(n)
void HashTable::display() {
    cout << "H: Hash Table" << endl;

    for(int i=0;i<SIZE;i++) {
        cout << i << ": ";
        HashNode* temp = table[i];

        while(temp != NULL) {
            cout << "[Zone " << temp->data.zoneID << "] -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

// H2: show only slots with collisions (more than one node at same index)
// Time Complexity: O(n)
void HashTable::showCollisions() {
    cout << "H2: Collision Slots:" << endl;

    bool found = false;
    for(int i=0;i<SIZE;i++) {
        if(table[i] != NULL && table[i]->next != NULL) {
            cout << "Index " << i << ": ";
            HashNode* temp = table[i];
            while(temp != NULL) {
                cout << "[Zone " << temp->data.zoneID << "] -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
            found = true;
        }
    }

    if(!found)
        cout << "H2: No collisions." << endl;
}

// H3: update cache with recently accessed zone
//removingg oldest when cache full (max 5)
void HashTable::updateCache(GridCell val) {
    for(int i=0;i<cacheSize;i++) {
        if(cacheKeys[i] == val.zoneID) {
            cacheData[i] = val;
            cout << "H3: Cache updated Zone " << val.zoneID << endl;
            return;
        }
    }

    if(cacheSize == 5) {
        for(int i=0;i<4;i++) {                  // shl
            cacheData[i] = cacheData[i+1];
            cacheKeys[i] = cacheKeys[i+1];
        }
        cacheSize = 4;
    }

    cacheData[cacheSize] = val;
    cacheKeys[cacheSize] = val.zoneID;
    cacheSize++;

    cout << "H3: Cached Zone!! " << val.zoneID << endl;
}

// H3: checking cache first,, fall back to main table on miss
// Time Complexity: O(1)
GridCell HashTable::searchCache(int zone) {
    for(int i=0; i<cacheSize;i++) {
        if(cacheKeys[i] == zone) {
            cout << "H3: Cache HIT Zone... " << zone << endl;
            return cacheData[i];
        }
    }

    cout << "H3: Cache MISS -> checking main table..." << endl;
    return search(zone);
}

void HashTable::displayCache() {
    cout << "H3: Cache:" << endl;

    for(int i=0;i<cacheSize;i++) {
        cout << "[" << i << "] Zone " << cacheKeys[i] << " Value:" << cacheData[i].value << endl;
    }
}
