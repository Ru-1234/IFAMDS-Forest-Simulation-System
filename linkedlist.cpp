#include "linkedlist.h"

// L1: raw event stream - stores sensor readings exactly as received, no filtering
// Storage rule: Data_stored = Data_sensor
// Time Complexity: O(n)
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

// time complexity : O(n)
void List::showL1() {
    cout << "L1 Raw Stream:" << endl;
    sllNode* temp = L1;
    while(temp != NULL) {
        cout << "Zone " << temp->data.zone << " | Value: " << temp->data.value << endl;
        temp = temp->next;
    }
}

// L2: verified event stream - noise removed before storing
// Noise rule: |Value_i - Value_i-1| >= delta => noise => reject
// Invalid: value < 0 OR value > 100 => reject
// Time Complexity: O(n)
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
            cout << "L2: Noise Detected -> |" << val.value << " - " << prev << "| = " << diff << " >= delta(" << delta << ") -> Rejected" << endl;
            return;
        }
    }

    sllNode* nn = new sllNode(val);

    if(L2 == NULL) {
        L2 = nn;
        nn->next = NULL;
    } 
    else {
        sllNode* temp = L2;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nn;            // append at end
        nn->next   = NULL;
    }

    cout << "L2: Verified Event Stored -> Zone " << val.zone << " | Value: " << val.value << endl;
}

// O(n)
void List::showL2() {
    cout << "L2 Verified Stream:" << endl;
    sllNode* temp = L2;
    while(temp != NULL) {
        cout << "Zone " << temp->data.zone << " | Value: " << temp->data.value << endl;
        temp = temp->next;
    }
}

// L3: anomaly stream - stores readings that deviate too far from normal
// Anomaly condition: |Value_current - Value_normal| > theta
// Normal = 25 (normal forest temperature)
// Time Complexity: O(n)
void List::storeAnomalyEvent(Event val, int theta) {
    float normal = 25;
    float diff = abs(val.value - normal);

    if(diff <= theta) {
        cout << val.value << " is not anomalous. Not stored." << endl;
        return;
    }

    sllNode* nn = new sllNode(val);
    if(L3 == NULL) { 
        L3 = nn;
        cout << "L3: Anomaly Stored -> Zone " << val.zone << " | Value: " << val.value << endl;
        return; 
    }
    sllNode* cur = L3;
    while(cur->next != NULL) 
        cur = cur->next;

    cur->next = nn;
    cout << "L3: Anomaly Stored -> Zone " << val.zone  << " | Value: " << val.value << endl;
}

// O(n)
void List::showL3() {
    cout << "L3 Anomaly Stream:" << endl;
    sllNode* temp = L3;
    while(temp != NULL) {
        cout << "Zone " << temp->data.zone << " | Value: " << temp->data.value << endl;
        temp = temp->next;
    }
}

// L4: forward correction chain , when past event corrected -> propagate change forward
// Event(i+1) = f(Event(i)) -> alpha increases +0.5 each step
// Time Complexity: O(n)
void List::forwardCorrection(int zone, int newValue) {   
    dllNode* temp = dllHead;
    if(!temp)
        return;

    float alpha = newValue;
    while(temp != NULL) {
        if(temp->data.zone == zone) {
            temp->data.value = newValue;

            dllNode* forward = temp->next;
            while(forward != NULL) {
                alpha += 0.5; 
                forward->data.value = alpha;
                forward = forward->next;
            }

            cout << "L4: Forward Correction Applied! " << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "L4: Zone not found for correction!" << endl;
}

// L5: backward correction chain , when new correct value found, fix previous events
// Event(i-1) = f(Event(i)) -> beta decreases -0.5 each step back
// Time Complexity: O(n)
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

// L6: state synchronization - all nodes = global base value
// Consistency rule: Event_all = Event_base
// Time Complexity: O(n)
void List::syncSystem() {
    if(L1 == NULL) return;

    int baseValue = L1->data.value;

    sllNode* temp = L1;

    while(temp != NULL) {
        temp->data.value = baseValue;
        temp = temp->next;
    }

    cout << "L6: System Synchronized" << endl;
}

// circular list insert - tail->next = head (loop)
// Time Complexity: O(1)
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

// L7: local monitoring - watch one zone in repeating cycle
// Cycle rule: Monitor(zone) -> repeat
// Time Complexity: O(n)
void List::localMonitor(int zone) {
    if(tail == NULL) 
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

// L8: system monitoring - scan all zones one after another
// Scan rule: sum of all zones
// Time Complexity: O(n)
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

// L9: emergency monitoring - activated when value > 50
// Trigger: Value > Threshold => Emergency
// Time Complexity: O(n)
void List::emergencyMonitor() {
    if(tail == NULL) 
        return;

    sllNode* temp = tail->next;     // tail->next = head

    cout << "L9: EMERGENCY MODE ACTIVATED!!!" << endl;

    do {
        if(temp->data.value > 50) {
            cout << "ALERT -> Zone " << temp->data.zone << endl;
        }
        temp = temp->next;
    } 
    while(temp != tail->next);
}

// L10: stability monitoring - check if values changing too much
// Stability condition: |Value_t - Value_t-1| < epsilon => stable
// Time Complexity: O(n)
void List::stabilityMonitor(int eps) {
    if(tail == NULL) 
        return;

    sllNode* temp = tail->next;    // head
    sllNode* prev = NULL;

    cout << "L10: Stability Monitor (eps=" << eps << ")" << endl;

    do {
        if(prev != NULL) {
            int diff = temp->data.value - prev->data.value;
            if(diff < 0) diff = -diff;

            if(diff < eps)
                cout << "Zone " << temp->data.zone << " -> STABLE (change=" << diff << ")" << endl;
            else
                cout << "Zone " << temp->data.zone << " -> UNSTABLE (change=" << diff << ")" << endl;
        }
        prev = temp;
        temp = temp->next;
    } 
    while(temp != tail->next);
}
