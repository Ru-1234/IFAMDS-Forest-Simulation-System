#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "data.h"

// L1-L3, L7-l10
// used for raw, verified, anomaly,emergency streams and circular monitoring
struct sllNode {
    Event data;
    sllNode* next;

    sllNode(Event val) : data(val) {next  = NULL;}
};
// L4-L6
struct dllNode {
    Event data;
    dllNode* prev;
    dllNode* next;

    dllNode(Event val) : data(val) {prev = next = NULL;}
};

// L1: Raw Event Stream Stores direct sensor readings without processing or filtering. Example: [25◦C, 28◦C, 30◦C]
// Storage rule: Datastored = Datasensor, Values stored exactly as received from sensors w/o modification.
class List {
    private:
        sllNode* L1;   // raw eveny stream
        sllNode* L2;   // L2
        sllNode* L3;   // L3

        dllNode* dllHead;      // for double linked list
        dllNode* dllTail;
        sllNode* tail;      // circular linked list
    public:
        List() {
            L1 = L2 = L3 = NULL;
            dllHead = dllTail = NULL;
            tail = NULL;
        }

        // L1
        void insertRawEvent(Event val);

        // L2
        void storeVerifiedEvent(Event val, int delta = 15);

        // L3
        void storeAnomalyEvent(Event val,int theta);       // Anomaly condition:   |Valuecurrent − Valuenormal| > θ

        // L4: Forward correction
        void forwardCorrection(int zone, int newValue);

        // L5: Backward correction
        void backwardCorrection(int zone, int newValue);

        // L6: Synchronization
        void syncSystem();

        // L7–L10 monitoring
        void insertCircular(Event val);
        void localMonitor(int zone);    // print all event for one zone
        void systemMonitor();           // print all events across all zones
        void emergencyMonitor();        // |Valuet − V aluet−1| < ε
        
        // utilities
        void insertInDLL(Event val){
            dllNode* nn = new dllNode(val);
            
            if(dllHead==NULL) {
                dllHead = dllTail = nn;
                return;
            }

            nn->prev = dllTail;
            dllTail->next = nn;
            dllTail = nn;
        }
};

#endif