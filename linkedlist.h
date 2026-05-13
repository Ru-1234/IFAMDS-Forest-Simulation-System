#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "data.h"

// L1-L3, L7-L10: singly linked list and circular
struct sllNode {
    Event data;
    sllNode* next;

    sllNode(Event val) : data(val) {next = NULL;}
};

// L4-L6: doubly linked list for forward/backward correction
struct dllNode {
    Event data;
    dllNode* prev;
    dllNode* next;

    dllNode(Event val) : data(val) {prev = next = NULL;}
};

class List {
    private:
        sllNode* L1;        // raw event stream
        sllNode* L2;        // verified event stream
        sllNode* L3;        // anomaly event stream

        dllNode* dllHead;   // doubly linked list
        dllNode* dllTail;

        sllNode* tail;      // circular list tail

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

        // L3: anomaly condition - |current - normal| > theta
        void storeAnomalyEvent(Event val, int theta);

        // L4: forward correction - Event(i+1) = f(Event(i))
        void forwardCorrection(int zone, int newValue);

        // L5: backward correction - Event(i-1) = f(Event(i))
        void backwardCorrection(int zone, int newValue);

        // L6: sync all nodes to base value
        void syncSystem();

        // L7-L10: circular monitoring
        void insertCircular(Event val);
        void localMonitor(int zone);
        void systemMonitor();
        void emergencyMonitor();
        void stabilityMonitor(int eps = 5);  // |Vt - Vt-1| < epsilon => stable

        // display helpers
        void showL1();
        void showL2();
        void showL3();

        void insertInDLL(Event val) {
            dllNode* nn = new dllNode(val);

            if(dllHead == NULL) {
                dllHead = dllTail = nn;
                return;
            }

            nn->prev = dllTail;
            dllTail->next = nn;
            dllTail = nn;
        }
};

#endif
