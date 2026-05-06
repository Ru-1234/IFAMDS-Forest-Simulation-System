#include "queue.h"

Queue::Queue() {
    Q1front = Q1rear = NULL;
    Q2front = Q2rear = NULL;
    Q3front = Q3rear = NULL;
    Q4front = Q4rear = NULL;
}

// Queue I - Routine Monitoring Queue 
void Queue::enqueueQ1(Event val) {
    Enqueue(val, Q1front, Q1rear);
    cout << "Q1: Enqueued Routine Task." << endl;
}

void Queue::dequeueQ1() {
    Event e = DequeueNode(Q1front, Q1rear);
    cout << "Q1: Dequeued Zone! " << e.zone << endl;

}

void Queue::processQ1() {
    cout << "Q1 Processing:" << endl;

    while(Q1front != NULL) {
        dequeueQ1();
    }
}

// Q2 SURVEILLANCE
void Queue::enqueueQ2(Event val) {
    Enqueue(val, Q2front, Q2rear);
    cout << "Q2: Enqueued Surveillance Task! " << endl;
}

void Queue::dequeueQ2() {
    Event e = DequeueNode(Q2front, Q2rear);
    cout << "Q2: Dequeued Zone " << e.zone << endl;
}

void Queue::processQ2() {
    cout << "Q2 Processing:" << endl;

    while(Q2front != NULL) {
        dequeueQ2();
    }
}

// Q3 EMERGENCY
void Queue::enqueueQ3(Event val) {
    Enqueue(val, Q3front, Q3rear);
    cout << "Q3: EMERGENCY ADDED" << endl;
}

void Queue::dequeueQ3() {
    Event e = DequeueNode(Q3front, Q3rear);
    cout << "Q3: ALERT Zone " << e.zone << endl;
}

void Queue::processQ3() {
    cout << "Q3 Processing:" << endl;

    while(Q3front != NULL) {
        dequeueQ3();
    }
}

// Q4 DECISION
void Queue::enqueueQ4(Event val) {
    Enqueue(val, Q4front, Q4rear);
    cout << "Q4: Decision Task Added! " << endl;
}

void Queue::dequeueQ4() {
    Event e = DequeueNode(Q4front, Q4rear);
    cout << "Q4: Processed Zone " << e.zone << endl;
}

void Queue::processQ4() {
    cout << "Q4 Processing:" << endl;

    while(Q4front != NULL) {
        dequeueQ4();
    }
}

//PRIORITY SWITCH
void Queue::promoteToEmergency(Event val) {
    QNode* nn = new QNode(val);

    if(Q3front == NULL) {
        Q3front = Q3rear = nn;
    } else {
        Q3rear->next = nn;
        Q3rear = nn;
    }

    cout << "PROMOTED TO EMERGENCY QUEUE" << endl;
}

// LOAD BALANCING
void Queue::balanceQueues() {
    if(Q2front != NULL) {

        QNode* temp = Q2front;
        Q2front = Q2front->next;

        if(Q2front == NULL)
            Q2rear = NULL;

        // move to Q1
        if(Q1front == NULL) {
            Q1front = Q1rear = temp;
            temp->next = NULL;
        } else {
            temp->next = NULL;
            Q1rear->next = temp;
            Q1rear = temp;
        }

        cout << "Balanced: Moved Q2 -> Q1" << endl;
    }
}
