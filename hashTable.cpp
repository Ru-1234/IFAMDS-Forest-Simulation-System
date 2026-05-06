#include "hashTable.h"

HashTable::HashTable() {
    for(int i=0;i<SIZE;i++)
        table[i] = NULL;
}

int HashTable::hashFunction(int key) {
    return key % SIZE;
}

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

    cout << "H: Inserted Zone " << val.zoneID << endl;
}

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