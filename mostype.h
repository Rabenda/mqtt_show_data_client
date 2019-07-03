#ifndef MOSTYPE_H
#define MOSTYPE_H

#include <QString>

struct sensor
{
    QString id;
    QString type;
    double val;
};

struct controller
{
    QString id;
    QString type;
    int val;
    sensor* bindSensor;
    float sensorThreshold;
    int openVal;
    int colseVal;
};

#endif // MOSTYPE_H
