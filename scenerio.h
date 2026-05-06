#ifndef SCENARIO_H
#define SCENARIO_H

#include "array.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"
#include "hashTable.h"
#include <iostream>
using namespace std;

class Scenario {
public:
    void fireScenario(Array &a, Queue &q, DecisionTree &t, Graph &g);
    void sensorFailureScenario(Array &a);
    void anomalyScenario(Array &a, Queue &q);
    void overloadScenario(Queue &q);
    void globalEmergency(Queue &q, Graph &g);
};

#endif