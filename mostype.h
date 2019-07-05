#ifndef MOSTYPE_H
#define MOSTYPE_H

#include <QString>

struct Sensor
{
    QString id;
    QString type;
    double data;
};

struct Controller
{
    QString id;
    QString type;
    int data;
    Sensor* bindSensor;
    float sensorThreshold;
    int openVal;
    int colseVal;
};

#endif // MOSTYPE_H
