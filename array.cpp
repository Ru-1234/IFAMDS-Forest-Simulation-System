#include "array.h"

// o (n^2)
Array::Array() {
    sizeA1 = 0;
    sizeA2 = 0;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            A3[i][j] = {0, 0, 0, 0};
            A4[i][j] = {0, 0, 0, 0};
        }
    }
}

// A1: static baseline - stores fixed normal forest reference values
// Time Complexity: o(1)
void Array::initBaseline(int t, int h, int s, int w) {
    A1[0] = {t, h, s, w};
    sizeA1 = 1;

    cout << "A1: Baseline initialized.." << endl;
}

// time complexity : o()
void Array::showBaseline() {
    cout << "A1 Baseline: " << endl;
    cout << "Temp: " << A1[0].temperature
         << " Humidity: " << A1[0].humidity
         << " Smoke: " << A1[0].smokelevel
         << " Wind: " << A1[0].windSpeed << endl;
}

// compare live A2 readings against A1 static baseline
// Time Complexity: o(n)
void Array::compareWithBaseline() {
    if(sizeA1 == 0) {
        cout << "A1: No baseline set!" << endl;
        return;
    }

    cout << "A1 vs A2 Comparison:" << endl;

    for(int i = 0; i < sizeA2; i++) {
        int tDiff = A2[i].temperature - A1[0].temperature;
        int sDiff = A2[i].smokelevel - A1[0].smokelevel;

        cout << "Reading " << i << ": TempDiff=" << tDiff << " SmokeDiff=" << sDiff;

        if(tDiff > 10 || sDiff > 20)
            cout << "[DEVIATION]";

        cout << endl;
    }
}

// A2: dynamic stream - stores live sensor readings that change during runtime
// Time Complexity: o(1)
void Array::insertSensor(int t, int h, int s, int w) {
    if(sizeA2 < MAX) {
        A2[sizeA2++] = {t, h, s, w};
        cout << "A2: Sensor inserted" << endl;
    }
}

// Time Complexity: o(n)
void Array::showStream() {
    cout << "A2 Stream:" << endl;

    for(int i = 0; i < sizeA2; i++) {
        cout << "T:" << A2[i].temperature
             << " H:" << A2[i].humidity
             << " S:" << A2[i].smokelevel
             << " W:" << A2[i].windSpeed << endl;
    }
}

// 1D time series - tracks temperature change over time from A2
// Time Complexity: o(n)
void Array::show1DTimeSeries() {
    cout << "A2 Time Series (Temperature):" << endl;

    for(int i = 0; i <sizeA2; i++) {
        cout << "[t" << i << "=" << A2[i].temperature << "] ";
    }
    cout << endl;
}

// A3: static forest grid - fixed 3x3 zone matrix
// Time Complexity: o(1)
void Array::initForestGrid() {
    SensorData base[3][3] = {
        {{25,60,0,5}, {30,55,5,6}, {28,58,2,7}},
        {{27,65,0,8}, {45,70,20,10}, {32,60,3,6}},
        {{26,62,1,4}, {29,59,0,5}, {31,61,2,6}}
    };

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            A3[i][j] = base[i][j];

    cout << "A3: Forest grid initialized! " << endl;
}

// Time Complexity: o(n*m)
void Array::showForestGrid() {
    cout << "A3 Forest Grid:" << endl;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "(" << A3[i][j].temperature << ","
                 << A3[i][j].humidity << "," << A3[i][j].smokelevel << ","
                 << A3[i][j].windSpeed << ") ";
        }
        cout << endl;
    }
}

// A4: dynamic terrain grid - values updated during runtime
// Time Complexity: o(1)
void Array::updateTerrain(int r, int c, int t, int h, int s, int w) {
    if(r < 10 && c < 10) {
        A4[r][c] = {t, h, s, w};
        cout << "A4 updated at (" << r << "," << c << ")" << endl;
    }
}

// Time Complexity: o(n*m)
void Array::showTerrain() {
    cout << "A4 Terrain Grid:" << endl;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "("
            << A4[i][j].temperature << "," << A4[i][j].humidity << ","
            << A4[i][j].smokelevel << "," << A4[i][j].windSpeed << ") ";
        }
        cout << endl;
    }
}

// boundary detection: sharp temp diff > 10 between neighbor zones = fire spread
// Time Complexity: O(n*m) , 2 * 2
void Array::detectBoundary() {
    cout << "Boundary Detection:" << endl;

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {

            int diff = A3[i][j].temperature - A3[i][j+1].temperature;
            if(diff < 0) 
                diff = -diff;

            if(diff > 10) {
                cout << "Boundary at (" << i << "," << j << ")" << endl;
            }
        }
    }
}

// threshold filter: flag anomalies based on sensor limits
// Rules: Temp > 45 OR Smoke level > 70 Or (Humidity <20 And Wind > 15)
// Time Complexity: o(n)
void Array::thresholdFilter() {
    cout << "Anomaly Detection:" << endl;

    for(int i = 0; i < sizeA2; i++) {
        if(A2[i].temperature > 45 || A2[i].smokelevel > 70 || (A2[i].humidity < 20 && A2[i].windSpeed > 15)) {
            cout << "ALERT at index " << i << endl;
        }
    }
}

// spatial interpolation: estimating missing zone value from 4 neighbors
// Formula: value = (top + bottom + left + right) / 4
// Time Complexity: o(1)
void Array::spatialInterpolation(int r, int c) {
    if(r > 0 && c > 0 && r < 2 && c < 2) {
        SensorData avg;
        avg.temperature = (A3[r-1][c].temperature + A3[r+1][c].temperature + A3[r][c-1].temperature + A3[r][c+1].temperature) / 4;

        avg.humidity = A3[r][c].humidity;
        avg.smokelevel = A3[r][c].smokelevel;
        avg.windSpeed = A3[r][c].windSpeed;

        A3[r][c] = avg;

        cout << "Interpolated at (" << r << "," << c << ")" << endl;
    }
}
