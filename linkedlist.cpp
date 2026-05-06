#include "linkedlist.h"

void List::insertRawEvent(Event val) {
    sllNode* nn = new sllNode(val);

    if(L1 == NULL) {
        L1 = nn;
        nn->next = NULL;
    } 
    else {
        sllNode* temp = L1;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nn;
        nn->next = NULL;
    }

    cout << "L1: Raw Event Inserted at end!" << endl;
}

void List::storeVerifiedEvent(Event val, int delta) {
    if(val.value < 0 || val.value > 100) {
        cout << "L2:Event Rejected, Value - out of bounds, must be between 1 and 100." << val.value << endl;
        return;
    }

    if(L2 != NULL) {
        sllNode* temp = L2;
        while(temp->next != NULL) {
            temp = temp->next;
        }

        int prev = temp->data.value;
        int diff = val.value - prev;
        if(diff < 0) 
            diff = -diff;   // absolute value

        if(diff >= delta) {
            cout << "L2: Noise Detected → |" << val.value << " - " << prev << "| = " << diff << " >= δ(" << delta << ") -> Rejected" << endl;
            return;
        }
    }

    sllNode* nn = new sllNode(val);

    if(L2 == NULL) {
        L2 = nn;
        nn->next     = NULL;
    } 
    else {
        sllNode* temp = L2;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nn;            // append at end
        nn->next   = NULL;
    }

    cout << "L2: Verified Event Stored → Zone " << val.zone << " | Value: " << val.value << endl;
}


void List::storeAnomalyEvent(Event val, int theta = 20) { // theta is safe threhold
    float normal = 25;
    float diff = abs(val.value - normal);

    if(diff <= theta) {
        cout << val.value << " is not anomalous. Not stored.\n";
        return;
    }

    sllNode* nn = new sllNode(val);
    if(L3==NULL) { 
        L3 = nn; 
        return; 
    }
    sllNode* cur = L3;
    while(cur->next!= NULL) 
        cur = cur->next;

    cur->next = nn;
    cout << "L3: Anomaly Stored -> Zone " << val.zone  << " | Value: " << val.value << endl;
}

// L4: Forward Correction Chain
// Event(i+1) = f(Event(i)) -> propagate correction forward
void List::forwardCorrection(int zone, int newValue) {   
    dllNode* temp = dllHead;
    if(!temp)
     return;

    float alpha = newValue;
    while(temp!=NULL){
        if(temp->data.zone == zone) {
            temp->data.value = newValue;

            dllNode* forward = temp->next;
            while(forward != NULL) {
                alpha += 0.5; 
                forward->data.value = alpha;
                forward = forward->next;
            }

            cout << "L4: Forward Correction Applied" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "L4: Zone not found for correction!" << endl;
}

// L5: Backward Correction Chain
// Event(i-1) = f(Event(i)) -> propagate correction backward
void List::backwardCorrection(int zone, int newValue) {
    dllNode* temp = dllHead;

    while(temp != NULL) {
        if(temp->data.zone == zone) {
            temp->data.value = newValue;

            dllNode* back = temp->prev;
            float beta = newValue;

            while(back != NULL) {
                beta -= 0.5;
                back->data.value = beta;
                back = back->prev;
            }

            cout << "L5: Backward Correction Applied" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "L5: Zone not found for correction!" << endl;
}

void List::syncSystem() {
    if(L1==NULL) return;

    int baseValue = L1->data.value;

    sllNode* temp = L1;

    while(temp != NULL) {
        temp->data.value = baseValue;
        temp = temp->next;
    }

    cout << "L6: System Synchronized" << endl;
}

// L6
void List::insertCircular(Event val) {
    sllNode* nn = new sllNode(val);

    if(tail == NULL) {
        tail = nn;
        tail->next = tail;
    } 
    else {
        nn->next = tail->next;
        tail->next = nn;
        tail = nn;
    }
}

// L7: LOCAL MONITORING
void List::localMonitor(int zone) {
    if(tail ==NULL) 
        return;

    sllNode* temp = tail->next;   // head

    cout << "L7: Local Monitoring Zone " << zone << endl;

    do {
        if(temp->data.zone == zone) {
            cout << "Value: " << temp->data.value << endl;
        }
        temp = temp->next;
    } while(temp != tail->next);
}


// L8: SYSTEM MONITORING
void List::systemMonitor() {
    if(tail == NULL) 
        return;

    sllNode* temp = tail->next;    // head

    cout << "L8: System Monitoring All Zones" << endl;

    do {
        cout << "Zone " << temp->data.zone << " | Value: " << temp->data.value << endl;
        temp = temp->next;
    } 
    while(temp != tail->next);
}


// L9 - emergency monitor
void List::emergencyMonitor() {
    if(tail==NULL) 
        return;

    sllNode* temp = tail->next;     // tail->nect : header

    cout << "L9: EMERGENCY MODE ACTIVATED!!!" << endl;

    do {
        if(temp->data.value > 50) {
            cout << "ALERT -> Zone " << temp->data.zone << endl;
        }
        temp = temp->next;
    } 
    while(temp != tail->next);
}