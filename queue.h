#ifndef QUEUE_H
#define QUEUE_H

#include "data.h"
#include <iostream>
using namespace std;

struct QNode {
    Event data;
    QNode* next;

    // time compexity O(1)
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
        bool   Q1paused;

        // Q2: Surveillance Queue
        QNode* Q2front;
        QNode* Q2rear;
        bool   Q2paused;

        // Q3: Emergency Queue
        QNode* Q3front;
        QNode* Q3rear;
        bool   Q3paused;

        // Q4: Multi-Factor Decision Queue
        QNode* Q4front;
        QNode* Q4rear;
        bool   Q4paused;

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

        // Q3 Priority Queue - sorted by value descending (highest severity first)
        // Time Complexity: Enqueue O(n), Dequeue O(1), Process O(n)
        void enqueueQ3(Event val);
        void dequeueQ3();
        void processQ3();
        void showQ3Priority(); 

        // Q4
        void enqueueQ4(Event val);
        void dequeueQ4();
        void processQ4();

        // priority switch
        void promoteToEmergency(Event val);

        // load balancing
        void balanceQueues();

        // pause / resume
        void pauseQueue(int qNum);
        void resumeQueue(int qNum);
        void showQueueStatus();

        // time complexity
        // insertion at tail (rear)
        void Enqueue(Event val, QNode* &front, QNode* &rear) {
            QNode* nn = new QNode(val);

            if(front == NULL) {
                front = rear = nn;
            } else {
                rear->next = nn;
                rear = nn;
            }
        }

        // time compexity : O(1)
        // deletion from head 
        Event DequeueNode(QNode* &front, QNode* &rear) {
            if(front == NULL) {
                cout << "Queue is Empty!" << endl;
                return {0, 0, 0};
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
