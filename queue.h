#ifndef QUEUE_H
#define QUEUE_H

#include "data.h"
#include <iostream>
using namespace std;

struct QNode {
    Event data;
    QNode* next;

    QNode(Event val) {
        data = val;
        next = NULL;
    }
};

class Queue {
    private:
        // Q1: Routine Monitoring Queue
        QNode* Q1front;
        QNode* Q1rear;
        // Q2: Surveillance Queue
        QNode* Q2front;
        QNode* Q2rear;
        // Q3: Emergency Queue
        QNode* Q3front;
        QNode* Q3rear;
        // Q4: Decision Queue
        QNode* Q4front;
        QNode* Q4rear;

    public:
        Queue();

        // Q1
        void enqueueQ1(Event val);
        void dequeueQ1();
        void processQ1();

        // Q2
        void enqueueQ2(Event val);
        void dequeueQ2();
        void processQ2();

        // Q3
        void enqueueQ3(Event val);
        void dequeueQ3();
        void processQ3();

        // Q4
        void enqueueQ4(Event val);
        void dequeueQ4();
        void processQ4();

        // Priority
        void promoteToEmergency(Event val);

        // Load balancing
        void balanceQueues();

        void Enqueue(Event val, QNode* &front, QNode* &rear) {
            QNode* nn = new QNode(val);

            if(Q1front == NULL) {
                front = rear = nn;      // no node
            } 
            else {
                rear->next = nn;
                rear = nn;
            }
        }

        Event DequeueNode(QNode* &front, QNode* &rear){
            if(front == NULL) {
                cout << "Queue is Empty!" << endl;
                return {0,0,0};
            }

            QNode* cur = front;
            front = front->next;

            if(front == NULL)
                rear = NULL;
            
            Event val = cur->data;
            delete cur;
            return val;
        }
};

#endif