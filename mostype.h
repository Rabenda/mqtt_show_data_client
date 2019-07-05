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
    double data;
    Sensor* bindSensor;
    float sensorThreshold;
    double openVal;
    double colseVal;
};

#endif // MOSTYPE_H
