#include "monitoring.h"

Monitor::Monitor() {
    startTime = endTime = 0;
    capacity = 50;
    bottleneck = "None";

    for(int i=0;i<4;i++)
        taskCounts[i] = 0;
}

// Time Complexity: O(1)
void Monitor::startTimer() {
    startTime = clock();
}

// Time Complexity: O(1)
void Monitor::stopTimer() {
    endTime = clock();
}

// Latency = (endTime - startTime) / CLOCKS_PER_SEC * 1000 ms
// Time Complexity: O(1)
float Monitor::getLatency() {
    return (float)(endTime - startTime) / CLOCKS_PER_SEC * 1000.0f;
}

// Time Complexity: O(1)
void Monitor::setTaskCount(int q, int count) {
    if(q >= 1 && q <= 4)
        taskCounts[q-1] = count;
}

// Load = Number of Active Tasks / Processing Capacity
// Time Complexity: O(1)
float Monitor::getLoad(int q) {
    if(q >= 1 && q <= 4)
        return (float)taskCounts[q-1] / capacity;
    return 0;
}

// Time Complexity: O(1) - fixed 4 queues
void Monitor::analyzeLoad() {
    cout << "SYS: Load Analysis:" << endl;

    string names[] = {"Q1-Routine", "Q2-Surveillance", "Q3-Emergency", "Q4-Decision"};

    for(int i=0;i<4;i++) {
        float load = getLoad(i+1);
        cout << names[i] << ": " << taskCounts[i] << " tasks | Load=" << load;

        if(load > 0.8)      cout << " [OVERLOADED]";
        else if(load > 0.5) cout << " [WARNING]";
        else                cout << " [OK]";
        cout << endl;
    }
}

// identifies slowest part delaying overall processing
// Time Complexity: O(1)
void Monitor::detectBottleneck() {
    int maxTasks = 0;
    int bottleneckQ = -1;
    string names[] = {"Q1", "Q2", "Q3", "Q4"};

    for(int i=0;i<4;i++) {
        if(taskCounts[i] > maxTasks) {
            maxTasks = taskCounts[i];
            bottleneckQ = i;
        }
    }

    if(bottleneckQ >= 0 && maxTasks > capacity / 2) {
        bottleneck = names[bottleneckQ];
        cout << "SYS: Bottleneck -> " << bottleneck << " (" << maxTasks << " tasks)" << endl;
    } else {
        cout << "SYS: No bottleneck." << endl;
    }
}

// Time Complexity: O(1)
void Monitor::showSystemHealth() {
    float latency = getLatency();

    cout << "SYS: System Health:" << endl;
    cout << "Latency: " << latency << " ms" << endl;
    cout << "Bottleneck: " << bottleneck << endl;
    analyzeLoad();

    if(latency < 5)       cout << "Status: HEALTHY" << endl;
    else if(latency < 20) cout << "Status: WARNING" << endl;
    else                  cout << "Status: CRITICAL" << endl;
}

// redistribute workload when queue overloaded
// Time Complexity: O(1)
void Monitor::optimizePerformance() {
    cout << "SYS: Optimizing..." << endl;

    for(int i=0;i<4;i++) {
        if(getLoad(i+1) > 0.8) {
            cout << "SYS: Redistributing Q" << (i+1) << endl;
            taskCounts[i] = capacity / 2;
        }
    }

    cout << "SYS: Optimization complete." << endl;
}
