#ifndef ARRAY_H
#define ARRAY_H
#include "data.h"

const int MAX = 100;

class Array {
    private:
        SensorData A1[10];          // A1: Static baseline
        int sizeA1;
        SensorData A2[MAX];        // A2: Live stream
        int sizeA2;
        SensorData A3[10][10];     // A3: Forest grid - static
        SensorData A4[10][10];     // A4: Terrain grid

  public:
      Array();

      // A1
      void initBaseline(int t, int h, int s, int w);
      void showBaseline();
      void compareWithBaseline();
  
      // A2
      void insertSensor(int t, int h, int s, int w);
      void showStream();
      void show1DTimeSeries();
  
      // A3
      void initForestGrid();
      void showForestGrid();
  
      // A4
      void updateTerrain(int r, int c, int t, int h, int s, int w);
      void showTerrain();
  
      // Operations
      void detectBoundary();                          // sharp temp diff > 10 between neighbor zones = fire spread
      void thresholdFilter();                         // Rule: (Temp > 45) || (Smoke level > 70) || (Humidity <20 && Wind > 15)
      void spatialInterpolation(int r, int c);        // estimating missing zone's value from 4 neighbors
};

#endif
