
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
    int taskType;     // routine / emergency / surveillance
    int priority;     // importance level
    string description;
};

struct GridCell {
    int zoneID;
    int value;   // risk level or combined sensor score
};

struct DecisionData {
    int zone;
    float risk;
};
#endif