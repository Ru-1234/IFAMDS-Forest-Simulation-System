#include "scenerio.h"

void Scenario::fireScenario(Array &a, Queue &q, DecisionTree &t, Graph &g) {

    cout << "\nSCENARIO 1: FIRE SPREAD\n";

    Event e = {80,1,2};
    q.enqueueQ3(e);

    DecisionData d = {2,0.9};
    t.insert(d);

    g.addEdge(2,3);
    g.addEdge(3,4);

    cout << "Fire spreading simulation activated\n";
}