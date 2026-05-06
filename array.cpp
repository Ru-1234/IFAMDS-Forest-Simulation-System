#include "array.h"

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

void Array::initBaseline(int t, int h, int s, int w) {
    A1[0] = {t, h, s, w};
    sizeA1 = 1;

    cout << "A1: Baseline initialized.." << endl;
}

void Array::showBaseline() {
    cout << "A1 Baseline: " << endl;
    cout << "Temp: " << A1[0].temperature
         << " Humidity: " << A1[0].humidity
         << " Smoke: " << A1[0].smokelevel
         << " Wind: " << A1[0].windSpeed << endl;
}

void Array::insertSensor(int t, int h, int s, int w) {
    if(sizeA2 < MAX) {
        A2[sizeA2++] = {t, h, s, w};
        cout << "A2: Sensor inserted" << endl;
    }
}

void Array::showStream() {
    cout << "A2 Stream:" << endl;

    for(int i = 0; i < sizeA2; i++) {
        cout << "T:" << A2[i].temperature
             << " H:" << A2[i].humidity
             << " S:" << A2[i].smokelevel
             << " W:" << A2[i].windSpeed << endl;
    }
}

void Array::initForestGrid() {
    SensorData base[3][3] = {
        {{25,60,0,5}, {30,55,5,6}, {28,58,2,7}},
        {{27,65,0,8}, {45,70,20,10}, {32,60,3,6}},
        {{26,62,1,4}, {29,59,0,5}, {31,61,2,6}}
    };

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            A3[i][j] = base[i][j];

    cout << "A3: Forest grid initialized" << endl;
}

void Array::showForestGrid() {
    cout << "A3 Forest Grid:" << endl;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "("
                 << A3[i][j].temperature << ","
                 << A3[i][j].humidity << ","
                 << A3[i][j].smokelevel << ","
                 << A3[i][j].windSpeed << ") ";
        }
        cout << endl;
    }
}

//A4 TERRAIN GRID 
void Array::updateTerrain(int r, int c, int t, int h, int s, int w) {
    if(r < 10 && c < 10) {
        A4[r][c] = {t, h, s, w};
        cout << "A4 updated at (" << r << "," << c << ")" << endl;
    }
}

void Array::showTerrain() {
    cout << "A4 Terrain Grid:" << endl;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "("
                 << A4[i][j].temperature << ","
                 << A4[i][j].humidity << ","
                 << A4[i][j].smokelevel << ","
                 << A4[i][j].windSpeed << ") ";
        }
        cout << endl;
    }
}

// BOUNDARY DETECTION
void Array::detectBoundary() {
    cout << "Boundary Detection:" << endl;

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j< 2; j++) {

            int diff = A3[i][j].temperature - A3[i][j+1].temperature;
            if(diff < 0) diff = -diff;

            if(diff > 10) {
                cout << "Boundary at (" << i << "," << j << ")" << endl;
            }
        }
    }
}

// THRESHOLD FILTER
void Array::thresholdFilter() {
    cout << "Anomaly Detection:" << endl;

    for(int i = 0; i < sizeA2; i++) {

        if(A2[i].temperature > 45 || A2[i].smokelevel > 70 || (A2[i].humidity < 20 && A2[i].windSpeed > 15)) {
            cout << "ALERT at index " << i << endl;
        }
    }
}

// SPATIAL INTERPOLATION
void Array::spatialInterpolation(int r, int c) {
    if(r > 0 && c > 0 && r < 2 && c < 2) {
        SensorData avg;
        avg.temperature = (A3[r-1][c].temperature + A3[r+1][c].temperature +
             A3[r][c-1].temperature + A3[r][c+1].temperature) / 4;

        avg.humidity = A3[r][c].humidity;
        avg.smokelevel = A3[r][c].smokelevel;
        avg.windSpeed = A3[r][c].windSpeed;

        A3[r][c] = avg;

        cout << "Interpolated at (" << r << "," << c << ")" << endl;
    }
}