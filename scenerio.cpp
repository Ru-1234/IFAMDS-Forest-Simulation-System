#include "scenerio.h"

// SCENARIO 1: CASCADING FIRE AND RESOURCE CONFLICT
// fire starts Zone 3, spreads to Zone 4 and Zone 6
// covers: Array anomaly, LinkedList raw+anomaly storage, Queue emergency, Graph BFS, Tree decision
void Scenario::fireScenario(Array &a, List &l, Queue &q, DecisionTree &t, Graph &g) {
    cout << "\n--- SCENARIO 1: CASCADING FIRE SPREAD ---" << endl;

    // Step 1: sensor detects fire conditions in Zone 3
    cout << "\n[Step 1] Fire sensors activated - Zone 3" << endl;
    a.insertSensor(70, 20, 80, 15);    // high temp, low humidity, high smoke
    a.thresholdFilter();               // anomaly detected immediately

    // Step 2: raw event stored in L1, anomaly flagged in L3
    cout << "\n[Step 2] Events stored in memory" << endl;
    Event e1 = {80, 1, 3};
    Event e2 = {85, 2, 4};
    l.insertRawEvent(e1);
    l.storeAnomalyEvent(e1, 20);
    l.insertRawEvent(e2);
    l.storeAnomalyEvent(e2, 20);
    l.insertCircular(e1);
    l.insertCircular(e2);

    // Step 3: emergency queue triggered
    cout << "\n[Step 3] Emergency queue triggered" << endl;
    q.enqueueQ3(e1);
    q.enqueueQ3(e2);

    // Step 4: BFS simulates fire spreading level by level
    cout << "\n[Step 4] Fire spread simulation (BFS from Zone 3)" << endl;
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.bfs(3);

    // Step 5: tree computes risk decision per zone
    cout << "\n[Step 5] Risk decision computed" << endl;
    t.insert({3, 0.9f});
    t.insert({4, 0.75f});
    t.insert({6, 0.5f});
    t.computeDecision(0.6f);

    // Step 6: process all emergency tasks
    cout << "\n[Step 6] Processing emergency tasks" << endl;
    q.processQ3();
    l.emergencyMonitor();

    cout << "\n[SCENARIO 1 COMPLETE]" << endl;
}

// SCENARIO 2: SENSOR FAILURE AND SYSTEM RECONSTRUCTION
// Zone 2 sensors send incomplete/incorrect readings
// covers: Array spatial interpolation, LinkedList backward correction L5, sync L6, stability L10
void Scenario::sensorFailureScenario(Array &a, List &l) {
    cout << "\n--- SCENARIO 2: SENSOR FAILURE ---" << endl;

    // Step 1: forest grid loaded - show current state
    cout << "\n[Step 1] Forest grid loaded" << endl;
    a.initForestGrid();
    a.showForestGrid();

    // Step 2: Zone (1,1) sensor failed - estimate from 4 neighbors
    // Formula: value = (top + bottom + left + right) / 4
    cout << "\n[Step 2] Zone (1,1) failed - spatial interpolation" << endl;
    a.spatialInterpolation(1, 1);

    // Step 3: backward correction fixes stored event history in DLL
    cout << "\n[Step 3] Backward correction on event history" << endl;
    l.insertInDLL({30, 1, 2});
    l.insertInDLL({35, 2, 2});
    l.insertInDLL({40, 3, 2});
    l.backwardCorrection(2, 30);

    // Step 4: sync all L1 nodes to consistent base value
    cout << "\n[Step 4] System sync after recovery" << endl;
    l.syncSystem();

    // Step 5: stability monitor confirms environment is back to normal
    cout << "\n[Step 5] Stability check post-recovery" << endl;
    l.stabilityMonitor(5);

    // Step 6: boundary detection confirms zone recovery
    cout << "\n[Step 6] Boundary check post-recovery" << endl;
    a.detectBoundary();

    cout << "\n[SCENARIO 2 COMPLETE]" << endl;
}

// SCENARIO 3: MULTI-FACTOR ANOMALY ESCALATION
// simultaneous: fire risk + wildlife movement + human intrusion
// covers: Array threshold, L3 anomaly, FireClassTree T7, WildlifeTree T8, HumanActivity T9, Queue
void Scenario::anomalyScenario(Array &a, List &l, Queue &q, FireClassTree &ft, WildlifeTree &wt, HumanActivityTree &ht) {
    cout << "\n--- SCENARIO 3: MULTI-FACTOR ANOMALY ---" << endl;

    // Step 1: multiple anomalous sensor readings arrive
    cout << "\n[Step 1] Multiple anomaly signals detected" << endl;
    a.insertSensor(60, 15, 90, 20);
    a.insertSensor(55, 18, 75, 18);
    a.thresholdFilter();

    // Step 2: anomalies stored in L3 stream
    cout << "\n[Step 2] Anomalies stored in L3 stream" << endl;
    Event e1 = {60, 1, 5};
    Event e2 = {55, 2, 6};
    l.storeAnomalyEvent(e1, 20);
    l.storeAnomalyEvent(e2, 20);

    // Step 3: fire classification T7 - Fire Level = 0.5*(Temp/100) + 0.5*(Smoke/100)
    cout << "\n[Step 3] Fire classification computed (T7)" << endl;
    ft.insert(5, 60, 90);
    ft.insert(6, 55, 75);
    ft.display();

    // Step 4: wildlife tree T8 - high activity means animals fleeing = fire confirmed
    cout << "\n[Step 4] Wildlife activity detected (T8)" << endl;
    wt.insert(5, 0.9f);
    wt.insert(6, 0.8f);
    wt.display();

    // Step 5: human activity T9 - Human Risk = Movement * RestrictedAreaFactor
    cout << "\n[Step 5] Human intrusion detected (T9)" << endl;
    ht.insert(5, 0.7f, 0.9f);
    ht.insert(6, 0.6f, 0.8f);
    ht.display();

    // Step 6: escalate all to emergency queue
    cout << "\n[Step 6] All anomalies escalated to emergency queue" << endl;
    q.promoteToEmergency({90, 1, 5});
    q.promoteToEmergency({75, 2, 6});
    q.enqueueQ2({55, 3, 7});
    q.enqueueQ2({60, 4, 8});

    // Step 7: process
    cout << "\n[Step 7] Processing all queues" << endl;
    q.processQ3();
    q.processQ2();

    cout << "\n[SCENARIO 3 COMPLETE]" << endl;
}

// SCENARIO 4: SYSTEM OVERLOAD AND LOAD REDISTRIBUTION
// large number of updates arrive simultaneously
// covers: Queue Q1-Q4 pause/resume, load balancing, Monitor latency+bottleneck
void Scenario::overloadScenario(Queue &q, Monitor &m) {
    cout << "\n--- SCENARIO 4: SYSTEM OVERLOAD ---" << endl;

    // Step 1: flood Q2 to simulate high traffic - timer running
    cout << "\n[Step 1] High traffic flooding Q2" << endl;
    m.startTimer();
    for(int i=0;i<5;i++) {
        q.enqueueQ2({20 + i, i, i + 1});
    }
    m.stopTimer();

    // Step 2: monitor detects overload
    cout << "\n[Step 2] Monitor analyzing load" << endl;
    m.setTaskCount(2, 30);
    m.setTaskCount(1, 1);
    m.analyzeLoad();
    m.detectBottleneck();

    // Step 3: pause low-priority queues during overload
    cout << "\n[Step 3] Pausing low-priority queues" << endl;
    q.pauseQueue(1);
    q.pauseQueue(4);
    q.showQueueStatus();

    // Step 4: rebalance - move tasks from overloaded Q2 to Q1
    cout << "\n[Step 4] Rebalancing Q2 -> Q1" << endl;
    q.balanceQueues();
    q.balanceQueues();

    // Step 5: resume all and process
    cout << "\n[Step 5] Resuming system" << endl;
    q.resumeQueue(1);
    q.resumeQueue(4);
    q.processQ1();
    q.processQ2();

    // Step 6: optimize and show health report
    cout << "\n[Step 6] Performance optimization" << endl;
    m.optimizePerformance();
    m.showSystemHealth();

    cout << "\n[SCENARIO 4 COMPLETE]" << endl;
}

// SCENARIO 5: GLOBAL MULTI-ZONE EMERGENCY SYNCHRONIZATION
// large-scale emergency across all zones simultaneously
// covers: Queue Q3, Graph DFS deep analysis, GlobalTree T12, HashTable H1+H2+H3, Monitor
void Scenario::globalEmergency(Queue &q, Graph &g, GlobalTree &gt, HashTable &h) {
    cout << "\n--- SCENARIO 5: GLOBAL EMERGENCY ---" << endl;

    // Step 1: all zones report critical conditions simultaneously
    cout << "\n[Step 1] Multi-zone emergency signals received" << endl;
    q.enqueueQ3({95, 1, 1});
    q.enqueueQ3({90, 1, 2});
    q.enqueueQ3({88, 1, 3});
    q.enqueueQ3({92, 1, 4});

    // Step 2: insert all zones into global risk tree T12
    cout << "\n[Step 2] Global risk tree updated" << endl;
    gt.insert({1, 0.95f});
    gt.insert({2, 0.9f});
    gt.insert({3, 0.88f});
    gt.insert({4, 0.92f});
    gt.display();

    // Step 3: sum(Risk_all_zones) > threshold => Global Alert
    cout << "\n[Step 3] Global alert check" << endl;
    gt.checkGlobalAlert(2.0f);

    // Step 4: DFS finds longest fire spread path in graph
    cout << "\n[Step 4] Deep path analysis (DFS)" << endl;
    g.startDFS(0);

    // Step 5: index all zone data in hash table for fast retrieval
    cout << "\n[Step 5] Zone data indexed in hash table" << endl;
    h.insert({1, 95});
    h.insert({2, 90});
    h.insert({3, 88});
    h.insert({4, 92});
    h.updateCache({1, 95});
    h.updateCache({2, 90});
    h.searchCache(1);
    h.searchCache(2);
    h.showCollisions();

    // Step 6: dispatch emergency response to all zones
    cout << "\n[Step 6] Emergency response dispatch" << endl;
    q.processQ3();

    cout << "\n[SCENARIO 5 COMPLETE]" << endl;
}
