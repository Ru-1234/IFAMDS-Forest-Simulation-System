#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
using namespace std;

struct SensorData {
    int temperature;
    int smokelevel;
    int humidity;
    int windSpeed;
};

struct Event {
    int value;
    int time;
    int zone;
};

struct Task {
    int taskType;
    int priority;
    string description;
};

struct GridCell {
    int zoneID;
    int value;
};

struct DecisionData {
    int zone;
    float risk;
};

#endif
