#ifndef ARRAY_H
#define ARRAY_H

#include "data.h"

const int MAX = 100;

class Array {
private:

    // A1: Static baseline
    SensorData A1[10];
    int sizeA1;

    // A2: Live stream
    SensorData A2[MAX];
    int sizeA2;

    // A3: Forest grid
    SensorData A3[10][10];

    // A4: Terrain grid
    SensorData A4[10][10];

public:
    Array();

    // A1
    void initBaseline(int t, int h, int s, int w);
    void showBaseline();

    // A2
    void insertSensor(int t, int h, int s, int w);
    void showStream();

    // A3
    void initForestGrid();
    void showForestGrid();

    // A4
    void updateTerrain(int r, int c, int t, int h, int s, int w);
    void showTerrain();

    // Operations
    void detectBoundary();
    void thresholdFilter();
    void spatialInterpolation(int r, int c);
};

#endif