#include <iostream>

#include "array.h"
#include "linkedlist.h"
#include "queue.h"
#include "graph.h"
#include "hashTable.h"
#include "tree.h"

using namespace std;

int main() {

    // ================= SYSTEM OBJECTS =================
    Array A;
    List L;
    Queue Q;

    Graph G(6);
    HashTable H;
    DecisionTree T;

    int choice;

    // ================= SAMPLE GRAPH SETUP =================
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,3);
    G.addEdge(2,4);
    G.addEdge(3,5);

    // ================= MENU LOOP =================
    do {

        cout << "\n========== IFAMDS FULL SYSTEM ==========\n";
        cout << "1. Sensor Input (Array + LinkedList)\n";
        cout << "2. View Array System\n";
        cout << "3. Linked List Monitoring System\n";
        cout << "4. Queue Task System\n";
        cout << "5. Graph (Fire Spread BFS/DFS)\n";
        cout << "6. Hash Table (Zone Indexing)\n";
        cout << "7. Decision Tree (Risk Analysis)\n";
        cout << "8. Run FULL SCENARIO SIMULATION\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

        // ================= INPUT SYSTEM =================
        case 1: {
            Event e;

            cout << "Enter Zone: ";
            cin >> e.zone;

            cout << "Enter Value: ";
            cin >> e.value;

            cout << "Enter Time: ";
            cin >> e.time;

            // ARRAY PIPELINE
            A.insertSensor(e.value, 50, 0, 10);

            // LINKED LIST PIPELINE
            L.insertRawEvent(e);
            L.storeVerifiedEvent(e, 15);
            L.storeAnomalyEvent(e, 20);

            L.insertCircular(e);
            L.insertInDLL(e);

            // HASH TABLE STORAGE
            H.insert({e.zone, e.value});

            // TREE DECISION INPUT
            T.insert({e.zone, (float)e.value / 100});

            cout << "System: Event processed successfully\n";
            break;
        }

        // ================= ARRAY VIEW =================
        case 2: {
            A.showStream();
            A.showForestGrid();
            A.showTerrain();
            A.detectBoundary();
            A.thresholdFilter();
            break;
        }

        // ================= LINKED LIST =================
        case 3: {
            int s;
            cout << "1. Local Monitor\n2. System Monitor\n3. Emergency Monitor\n4. Sync\n";
            cin >> s;

            if(s == 1) L.localMonitor(1);
            else if(s == 2) L.systemMonitor();
            else if(s == 3) L.emergencyMonitor();
            else if(s == 4) L.syncSystem();

            break;
        }

        // ================= QUEUE SYSTEM =================
        case 4: {
            int q;
            Event e;

            cout << "1. Q1 Routine\n2. Q2 Surveillance\n3. Q3 Emergency\n4. Process All\n";
            cin >> q;

            if(q != 4) {
                cout << "Enter zone, value, time: ";
                cin >> e.zone >> e.value >> e.time;
            }

            if(q == 1) Q.enqueueQ1(e);
            else if(q == 2) Q.enqueueQ2(e);
            else if(q == 3) Q.enqueueQ3(e);
            else if(q == 4) {
                Q.processQ1();
                Q.processQ2();
                Q.processQ3();
                Q.processQ4();
            }

            break;
        }

        // ================= GRAPH SYSTEM =================
        case 5: {
            int start;
            cout << "Enter start node (0-5): ";
            cin >> start;

            G.showMatrix();
            G.bfs(start);
            G.startDFS(start);

            break;
        }

        // ================= HASH TABLE =================
        case 6: {
            int z;
            cout << "Enter zone to search: ";
            cin >> z;

            H.display();
            H.search(z);

            break;
        }

        // ================= TREE SYSTEM =================
        case 7: {
            float threshold;
            cout << "Enter risk threshold (0-1): ";
            cin >> threshold;

            T.displayTree();
            T.computeDecision(threshold);

            break;
        }

        // ================= FULL SCENARIO SIMULATION =================
        case 8: {
            cout << "\n========== SCENARIO SIMULATION ==========\n";

            // 🔥 SCENARIO 1: FIRE SPREAD
            cout << "\n[SCENARIO 1: FIRE SPREAD]\n";
            G.bfs(0);
            Q.enqueueQ3({1, 90, 3});
            Q.processQ3();

            // 🔥 SCENARIO 2: SENSOR FAILURE
            cout << "\n[SCENARIO 2: SENSOR FAILURE]\n";
            L.syncSystem();

            // 🔥 SCENARIO 3: ANOMALY DETECTION
            cout << "\n[SCENARIO 3: ANOMALY CHECK]\n";
            A.thresholdFilter();

            // 🔥 SCENARIO 4: LOAD SYSTEM
            cout << "\n[SCENARIO 4: LOAD BALANCING]\n";
            Q.balanceQueues();

            // 🔥 SCENARIO 5: GLOBAL EMERGENCY
            cout << "\n[SCENARIO 5: GLOBAL DECISION]\n";
            T.computeDecision(0.6);

            cout << "\nAll scenarios executed successfully.\n";
            break;
        }

        // ================= EXIT =================
        case 0: {
            cout << "Exiting IFAMDS System...\n";
            break;
        }

        default:
            cout << "Invalid choice!\n";
        }

    } while(choice != 0);

    return 0;
}