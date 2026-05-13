#ifndef SCENARIO_H
#define SCENARIO_H

#include "array.h"
#include "linkedlist.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"
#include "hashTable.h"
#include "monitoring.h"
#include <iostream>
using namespace std;

class Scenario {
public:
    void fireScenario(Array &a, List &l, Queue &q, DecisionTree &t, Graph &g);
    void sensorFailureScenario(Array &a, List &l);
    void anomalyScenario(Array &a, List &l, Queue &q, FireClassTree &ft, WildlifeTree &wt, HumanActivityTree &ht);
    void overloadScenario(Queue &q, Monitor &m);
    void globalEmergency(Queue &q, Graph &g, GlobalTree &gt, HashTable &h);
};

#endif
