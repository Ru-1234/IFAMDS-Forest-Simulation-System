#ifndef MONITORING_H
#define MONITORING_H

#include "data.h"
#include <ctime>
#include <iostream>
using namespace std;

class Monitor {
private:
    clock_t startTime;
    clock_t endTime;

    int taskCounts[4];   // tasks in Q1, Q2, Q3, Q4
    int capacity;        // max tasks per queue
    string bottleneck;

public:
    Monitor();

    // Latency = FinishTime - StartTime
    void startTimer();
    void stopTimer();
    float getLatency();

    // Load = ActiveTasks / Capacity
    void setTaskCount(int q, int count);
    float getLoad(int q);
    void analyzeLoad();

    void detectBottleneck();
    void showSystemHealth();
    void optimizePerformance();
};

#endif
