#ifndef SENSOR_HPP
#define SENSOR_HPP
#include <QObject>

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENSOR_HPP
