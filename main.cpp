#include <iostream>
#include "array.h"
#include "linkedlist.h"
#include "queue.h"
#include "graph.h"
#include "hashTable.h"
#include "tree.h"
#include "monitoring.h"
#include "scenerio.h"

using namespace std;

int main() {

    //SYSTEM OBJECTS
    Array A;
    List L;
    Queue Q;

    Graph G(6);
    GraphList GL(6);
    HashTable H;
// trees
    DecisionTree T;
    ZoneHierarchyTree T1;
    SubZoneTree T2;
    TerrainTree T3;
    WaterTree T4;
    FireControlTree T5;
    EquipmentTree T6;
    FireClassTree T7;
    WildlifeTree T8;
    HumanActivityTree T9;
    RegionalTree T11;
    GlobalTree T12;

    Monitor M;
    Scenario S;

    int choice;

    // SAMPLE GRAPH SETUP
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(1,3);
    G.addEdge(2,4);
    G.addEdge(3,5);

    GL.addEdge(0,1);
    GL.addEdge(0,2);
    GL.addEdge(1,3);
    GL.addEdge(2,4);
    GL.addEdge(3,5);

    //BASELINE SETUP
    A.initBaseline(25, 60, 0, 5);
    A.initForestGrid();

    T1.build();
    T2.build();

    do {

        cout << "````````````````````````````````````````````````" << endl;
        cout << "`            IFAMDS MAIN MENU                  `" << endl;
        cout << "````````````````````````````````````````````````" << endl;
        cout << "1.  Input Environmental Data" << endl;
        cout << "2.  View Forest Grid Status" << endl;
        cout << "3.  Event Memory System" << endl;
        cout << "4.  Fire Detection and Control" << endl;
        cout << "5.  Task Scheduling System" << endl;
        cout << "6.  Decision System" << endl;
        cout << "7.  Spatial Routing System" << endl;
        cout << "8.  Hash-Based Fast Access System" << endl;
        cout << "9.  System Monitoring" << endl;
        cout << "10. Scenario Simulation" << endl;
        cout << "0.  Exit System" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

        //  1. INPUT ENVIRONMENTAL DATA 
        case 1: {
            int sub;
            cout << "\n--- Input Environmental Data ---" << endl;
            cout << "1.1 Add Sensor Reading" << endl;
            cout << "1.2 Store Data in Dynamic Array" << endl;
            cout << "1.3 Compare with Static Baseline" << endl;
            cout << "1.4 Validate and Filter Noise" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                Event e;
                cout << "Enter Zone: "; cin >> e.zone;
                cout << "Enter Value (temp): "; cin >> e.value;
                cout << "Enter Time: "; cin >> e.time;

                A.insertSensor(e.value, 50, 5, 10);

                L.insertRawEvent(e);
                L.storeVerifiedEvent(e, 15);
                L.storeAnomalyEvent(e, 20);
                L.insertCircular(e);
                L.insertInDLL(e);

                H.insert({e.zone, e.value});
                H.updateCache({e.zone, e.value});

                T.insert({e.zone, (float)e.value / 100});
                T12.insert({e.zone, (float)e.value / 100});

                cout << "System: Event processed successfully" << endl;
            }
            else if(sub == 2) {
                int t, h, s, w;
                cout << "Enter Temp Humidity Smoke Wind: ";
                cin >> t >> h >> s >> w;
                A.insertSensor(t, h, s, w);
                A.showStream();
            }
            else if(sub == 3) {
                A.compareWithBaseline();
            }
            else if(sub == 4) {
                A.thresholdFilter();
            }
            break;
        }

        //  2. VIEW FOREST GRID STATUS 
        case 2: {
            int sub;
            cout << "\n--- View Forest Grid Status ---" << endl;
            cout << "2.1 Display 1D Time Series Data" << endl;
            cout << "2.2 Display 2D Forest Zone Matrix" << endl;
            cout << "2.3 View Zone-wise Conditions" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1)      
                A.show1DTimeSeries();
            else if(sub == 2) 
                A.showForestGrid();
            else if(sub == 3) { 
                A.showStream(); 
                A.showTerrain(); }

            break;
        }

        //  3. EVENT MEMORY SYSTEM 
        case 3: {
            int sub;
            cout << "\n--- Event Memory System ---" << endl;
            cout << "3.1 Store Event (Linked List)" << endl;
            cout << "3.2 Traverse Event History Forward" << endl;
            cout << "3.3 Traverse Event History Backward" << endl;
            cout << "3.4 Circular Event Monitoring" << endl;
            cout << "3.5 Restore Last Stable State" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                Event e;
                cout << "Zone Value Time: ";
                cin >> e.zone >> e.value >> e.time;
                L.insertRawEvent(e);
                L.storeVerifiedEvent(e, 15);
                L.storeAnomalyEvent(e, 20);
            }
            else if(sub == 2) {
                L.showL1();
                L.showL2();
            }
            else if(sub == 3) {
                int zone, val;
                cout << "Enter zone and corrected value: ";
                cin >> zone >> val;
                L.backwardCorrection(zone, val);
            }
            else if(sub == 4) {
                int s;
                cout << "1. Local Monitor  2. System Monitor  3. Emergency  4. Stability" << endl;
                cin >> s;
                if(s == 1) { 
                    int z; 
                    cout << "Zone: "; 
                    cin >> z; 
                    L.localMonitor(z); }
                else if(s == 2) 
                    L.systemMonitor();
                else if(s == 3) 
                    L.emergencyMonitor();
                else if(s == 4) 
                    L.stabilityMonitor(5);
            }
            else if(sub == 5) {
                L.syncSystem();
            }

            break;
        }

        //  4. FIRE DETECTION AND CONTROL 
        case 4: {
            int sub;
            cout << "\n--- Fire Detection and Control ---" << endl;
            cout << "4.1 Detect Fire Risk (Threshold Check)" << endl;
            cout << "4.2 Trigger Emergency Alert" << endl;
            cout << "4.3 Priority-Based Fire Response" << endl;
            cout << "4.4 Simulate Fire Spread (Graph BFS)" << endl;
            cout << "4.5 Allocate Firefighting Resources" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                A.thresholdFilter();
                A.detectBoundary();
            }
            else if(sub == 2) {
                Event e;
                cout << "Zone Value Time: ";
                cin >> e.zone >> e.value >> e.time;
                Q.enqueueQ3(e);
                Q.processQ3();
            }
            else if(sub == 3) {
                Event e;
                cout << "Zone Value Time: ";
                cin >> e.zone >> e.value >> e.time;
                Q.promoteToEmergency(e);
                Q.processQ3();
            }
            else if(sub == 4) {
                int start;
                cout << "Enter start zone (0-5): ";
                cin >> start;
                G.bfs(start);
                G.startDFS(start);
            }
            else if(sub == 5) {
                int zone;
                float res;
                cout << "Zone ResourceLevel: ";
                cin >> zone >> res;
                T5.insert(zone, res);
                T6.insert(zone, res, 0.8f);
                T5.display();
                T6.display();
            }

            break;
        }

        //  5. TASK SCHEDULING SYSTEM 
        case 5: {
            int sub;
            cout << "\n--- Task Scheduling System ---" << endl;
            cout << "5.1 Add Routine Task (Queue)" << endl;
            cout << "5.2 Add Surveillance Task" << endl;
            cout << "5.3 Add Emergency Task (Priority Queue)" << endl;
            cout << "5.4 Process Tasks (FIFO / Priority)" << endl;
            cout << "5.5 Pause and Resume Tasks" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                Event e;
                cout << "Zone Value Time: ";
                cin >> e.zone >> e.value >> e.time;
                Q.enqueueQ1(e);
            }
            else if(sub == 2) {
                Event e;
                cout << "Zone Value Time: ";
                cin >> e.zone >> e.value >> e.time;
                Q.enqueueQ2(e);
            }
            else if(sub == 3) {
                Event e;
                cout << "Zone Value Time: ";
                cin >> e.zone >> e.value >> e.time;
                Q.enqueueQ3(e);
                Q.showQ3Priority();
            }
            else if(sub == 4) {
                Q.processQ1();
                Q.processQ2();
                Q.processQ3();
                Q.processQ4();
            }
            else if(sub == 5) {
                int s;
                cout << "1. Pause  2. Resume  3. Status" << endl;
                cin >> s;
                if(s == 1) {
                    int q; cout << "Queue number (1-4): "; cin >> q;
                    Q.pauseQueue(q);
                }
                else if(s == 2) {
                    int q; cout << "Queue number (1-4): "; cin >> q;
                    Q.resumeQueue(q);
                }
                else if(s == 3) Q.showQueueStatus();
            }

            break;
        }

        //  6. DECISION SYSTEM 
        case 6: {
            int sub;
            cout << "\n--- Decision System ---" << endl;
            cout << "6.1 Compute Risk Score" << endl;
            cout << "6.2 Zone-Level Decision Tree" << endl;
            cout << "6.3 Regional Decision Processing" << endl;
            cout << "6.4 Global Emergency Decision" << endl;
            cout << "6.5 Execute Final Action" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                // Decision Score = w1(Fire) + w2(Smoke) + w3(Temp)
                float fire, smoke, temp;
                cout << "Enter Fire Smoke Temp (0-1 each): ";
                cin >> fire >> smoke >> temp;
                float score = 0.4f * fire + 0.3f * smoke + 0.3f * temp;
                cout << "Decision Score = " << score << endl;
                if(score > 0.6) 
                    cout << "=> EMERGENCY ACTIVATED" << endl;
                else
                    cout << "=> Normal" << endl;
            }
            else if(sub == 2) {
                float threshold;
                cout << "Enter risk threshold (0-1): ";
                cin >> threshold;
                T.displayTree();
                T.computeDecision(threshold);
            }
            else if(sub == 3) {
                T11.display();
            }
            else if(sub == 4) {
                float threshold;
                cout << "Enter global threshold: ";
                cin >> threshold;
                T12.display();
                T12.checkGlobalAlert(threshold);
            }
            else if(sub == 5) {
                // final action - run full decision chain
                T.computeDecision(0.6f);
                T11.escalate(0.5f);
                T12.checkGlobalAlert(2.0f);
                Q.processQ3();
            }

            break;
        }

        //  7. SPATIAL ROUTING SYSTEM 
        case 7: {
            int sub;
            cout << "\n--- Spatial Routing System ---" << endl;
            cout << "7.1 Load Graph (Adjacency List)" << endl;
            cout << "7.2 Load Graph (Adjacency Matrix)" << endl;
            cout << "7.3 BFS Traversal (Fire Spread)" << endl;
            cout << "7.4 DFS Traversal (Deep Analysis)" << endl;
            cout << "7.5 Compute Safe Path" << endl;
            cout << "7.6 Update Blocked Routes" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                GL.display();
            }
            else if(sub == 2) {
                G.showMatrix();
            }
            else if(sub == 3) {
                int start;
                cout << "Enter start node (0-5): ";
                cin >> start;
                cout << "G1 "; GL.bfs(start);
                G.bfs(start);
            }
            else if(sub == 4) {
                int start;
                cout << "Enter start node (0-5): ";
                cin >> start;
                GL.startDFS(start);
                G.startDFS(start);
            }
            else if(sub == 5) {
                int u, v, dist, danger;
                cout << "Enter u v distance danger: ";
                cin >> u >> v >> dist >> danger;
                GL.pathCost(u, v, dist, danger);
            }
            else if(sub == 6) {
                int u, v, dist;
                float fireLevel;
                cout << "Enter u v distance fireLevel: ";
                cin >> u >> v >> dist >> fireLevel;
                GL.updateFireCost(u, v, dist, fireLevel);
            }

            break;
        }

        //  8. HASH-BASED FAST ACCESS SYSTEM 
        case 8: {
            int sub;
            cout << "\n--- Hash-Based Fast Access System ---" << endl;
            cout << "8.1 Insert Data (Hash Table)" << endl;
            cout << "8.2 Retrieve Data (O(1) Access)" << endl;
            cout << "8.3 Handle Collisions" << endl;
            cout << "8.4 Update Cache" << endl;
            cout << "8.5 View Index Table" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                int zone, val;
                cout << "Zone Value: ";
                cin >> zone >> val;
                H.insert({zone, val});
            }
            else if(sub == 2) {
                int zone;
                cout << "Zone: ";
                cin >> zone;
                H.searchCache(zone);
            }
            else if(sub == 3) {
                H.showCollisions();
            }
            else if(sub == 4) {
                int zone, val;
                cout << "Zone Value: ";
                cin >> zone >> val;
                H.updateCache({zone, val});
                H.displayCache();
            }
            else if(sub == 5) {
                H.display();
            }

            break;
        }

        //  9. SYSTEM MONITORING 
        case 9: {
            int sub;
            cout << "\n--- System Monitoring ---" << endl;
            cout << "9.1 Monitor System Load" << endl;
            cout << "9.2 Track Execution Time" << endl;
            cout << "9.3 Detect Bottlenecks" << endl;
            cout << "9.4 Optimize Performance" << endl;
            cout << "9.5 View System Health" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1) {
                int q, count;
                cout << "Queue number (1-4) and task count: ";
                cin >> q >> count;
                M.setTaskCount(q, count);
                M.analyzeLoad();
            }
            else if(sub == 2) {
                M.startTimer();
                // simulate some work
                for(int i=0;i<1000;i++) {}
                M.stopTimer();
                cout << "Latency: " << M.getLatency() << " ms" << endl;
            }
            else if(sub == 3) {
                M.detectBottleneck();
            }
            else if(sub == 4) {
                M.optimizePerformance();
            }
            else if(sub == 5) {
                M.showSystemHealth();
            }

            break;
        }

        //  10. SCENARIO SIMULATION 
        case 10: {
            int sub;
            cout << "\n--- Scenario Simulation ---" << endl;
            cout << "10.1 Cascading Fire Scenario" << endl;
            cout << "10.2 Sensor Failure Scenario" << endl;
            cout << "10.3 Multi-Factor Anomaly Scenario" << endl;
            cout << "10.4 System Overload Scenario" << endl;
            cout << "10.5 Global Emergency Scenario" << endl;
            cout << "10.6 Run Full System Simulation" << endl;
            cout << "Enter: ";
            cin >> sub;

            if(sub == 1)      
                S.fireScenario(A, L, Q, T, G);
            else if(sub == 2) 
                S.sensorFailureScenario(A, L);
            else if(sub == 3) 
                S.anomalyScenario(A, L, Q, T7, T8, T9);
            else if(sub == 4) 
                S.overloadScenario(Q, M);
            else if(sub == 5) 
                S.globalEmergency(Q, G, T12, H);
            else if(sub == 6) {
                cout << "\n FULL SYSTEM SIMULATION " << endl;
                S.fireScenario(A, L, Q, T, G);
                S.sensorFailureScenario(A, L);
                S.anomalyScenario(A, L, Q, T7, T8, T9);
                S.overloadScenario(Q, M);
                S.globalEmergency(Q, G, T12, H);
                cout << "\nFull simulation complete." << endl;
            }

            break;
        }

        //  EXIT 
        case 0: {
            cout << "Exiting IFAMDS System..." << endl;
            break;
        }

        default:
            cout << "Invalid choice!" << endl;
        }

    } while(choice != 0);

    return 0;
}
