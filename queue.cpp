#include "queue.h"

// O(1)
Queue::Queue() {
    Q1front = Q1rear = NULL;  Q1paused = false;
    Q2front = Q2rear = NULL;  Q2paused = false;
    Q3front = Q3rear = NULL;  Q3paused = false;
    Q4front = Q4rear = NULL;  Q4paused = false;
}

// Q1: Routine Monitoring Queue - normal sensor updates, not urgent
// FIFO: first task added is first processed
// Time Complexity: Enqueue O(1), Dequeue O(1), Process O(n)
void Queue::enqueueQ1(Event val) {
    Enqueue(val, Q1front, Q1rear);
    cout << "Q1: Enqueued Routine Task." << endl;
}

void Queue::dequeueQ1() {
    Event e = DequeueNode(Q1front, Q1rear);
    cout << "Q1: Dequeued Zone " << e.zone << endl;
}

void Queue::processQ1() {
    if(Q1paused) { cout << "Q1: Paused :( " << endl; return; }

    cout << "Q1 Processing:" << endl;
    while(Q1front != NULL) {
        dequeueQ1();
    }
}

// Q2 SURVEILLANCE - frequent updates from sensitive zones
// Time Complexity: Enqueue O(1), Dequeue O(1), Process O(n)
void Queue::enqueueQ2(Event val) {
    Enqueue(val, Q2front, Q2rear);
    cout << "Q2: Enqueued Surveillance Task!" << endl;
}

void Queue::dequeueQ2() {
    Event e = DequeueNode(Q2front, Q2rear);
    cout << "Q2: Dequeued Zone " << e.zone << endl;
}

void Queue::processQ2() {
    if(Q2paused) { cout << "Q2: Paused :( " << endl; return; }

    cout << "Q2 Processing:" << endl;
    while(Q2front != NULL) {
        dequeueQ2();
    }
}

// Q3 EMERGENCY PRIORITY QUEUE - sorted by value descending
// Time Complexity: Enqueue O(n), Dequeue O(1), Process O(n)
// Higher value = more critical = processed first =>  Insertion in sorted position
void Queue::enqueueQ3(Event val) {
    QNode* nn = new QNode(val);

    // at front if highest
    if(Q3front == NULL || val.value > Q3front->data.value) {
        nn->next = Q3front;
        Q3front = nn;
        if(Q3rear == NULL) 
            Q3rear = nn;
        cout << "Q3: EMERGENCY ADDED (Priority=" << val.value << ") -> Front" << endl;
        return;
    }

    // finding correct sorted position
    QNode* temp = Q3front;
    while(temp->next != NULL && temp->next->data.value >= val.value) {
        temp = temp->next;
    }

    nn->next = temp->next;
    temp->next = nn;
    if(nn->next == NULL) Q3rear = nn;

    cout << "Q3: EMERGENCY ADDED (Priority=" << val.value << ")" << endl;
}

// display Q3 in priority order (highest to lowest)
// Time Complexity: O(n)
void Queue::showQ3Priority() {
    cout << "Q3 Priority Order (highest first):" << endl;
    QNode* temp = Q3front;
    int rank = 1;
    while(temp != NULL) {
        cout << rank++ << ". Zone " << temp->data.zone << " | Severity=" << temp->data.value << endl;
        temp = temp->next;
    }
    if(Q3front == NULL) 
        cout << "Q3 is empty." << endl;
}

void Queue::dequeueQ3() {
    Event e = DequeueNode(Q3front, Q3rear);
    cout << "Q3: ALERT Zone " << e.zone << endl;
}

void Queue::processQ3() {
    if(Q3paused) { cout << "Q3: Paused :( " << endl; return; }

    cout << "Q3 Processing:" << endl;
    while(Q3front != NULL) {
        dequeueQ3();
    }
}

// Q4 DECISION - multi-factor tasks: Temp + Smoke + Wind => decision
// Time Complexity: Enqueue O(1), Dequeue O(1), Process O(n)
void Queue::enqueueQ4(Event val) {
    Enqueue(val, Q4front, Q4rear);
    cout << "Q4: Decision Task Added!" << endl;
}

void Queue::dequeueQ4() {
    Event e = DequeueNode(Q4front, Q4rear);
    cout << "Q4: Processed Zone " << e.zone << endl;
}

void Queue::processQ4() {
    if(Q4paused) { cout << "Q4: Paused :( " << endl; return; }

    cout << "Q4 Processing:" << endl;
    while(Q4front != NULL) {
        dequeueQ4();
    }
}

// PRIORITY SWITCH - move task straight to   the emergency queue
// Time Complexity: O(1)
void Queue::promoteToEmergency(Event val) {
    enqueueQ3(val);
    cout << "PROMOTED TO EMERGENCY QUEUE!!!" << endl;
}

// LOAD BALANCING - move task from heavy Q2 to Q1
// Time Complexity: O(1)
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

// PAUSE /RESUME - skip processing until resumed
// Time Complexity: O(1)
void Queue::pauseQueue(int qNum) {
    if(qNum == 1){ 
        Q1paused = true; 
        cout << "Q1: Paused" << endl; 
    }
    else if(qNum == 2) { 
        Q2paused = true; 
        cout << "Q2: Paused" << endl; 
    }
    else if(qNum == 3) { 
        Q3paused = true; 
        cout << "Q3: Paused" << endl;
    }
    else if(qNum == 4) { 
        Q4paused = true; 
        cout << "Q4: Paused" << endl; 
    }
}

void Queue::resumeQueue(int qNum) {
    if(qNum == 1) { 
        Q1paused = false;
        cout << "Q1: Resumed" << endl; 
    }
    else if(qNum == 2) { 
        Q2paused = false; 
        cout << "Q2: Resumed" << endl; 
    }
    else if(qNum == 3) { 
        Q3paused = false; 
        cout << "Q3: Resumed" << endl; 
    }
    else if(qNum == 4) {
        Q4paused = false; 
        cout << "Q4: Resumed" << endl; 
    }
}

// O(1)
void Queue::showQueueStatus() {
    cout << "Queue Status:" << endl;
    cout << "Q1 (Routine):      " << (Q1paused ? "PAUSED" : "RUNNING") << endl;
    cout << "Q2 (Surveillance): " << (Q2paused ? "PAUSED" : "RUNNING") << endl;
    cout << "Q3 (Emergency):    " << (Q3paused ? "PAUSED" : "RUNNING") << endl;
    cout << "Q4 (Decision):     " << (Q4paused ? "PAUSED" : "RUNNING") << endl;
}
