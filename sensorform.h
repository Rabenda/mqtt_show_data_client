#ifndef SENSORFORM_H
#define SENSORFORM_H

#include <QWidget>

namespace Ui {
class SensorForm;
}

class SensorForm : public QWidget
{
    Q_OBJECT

public:
    explicit SensorForm(QWidget *parent = nullptr);
    ~SensorForm();

private:
    Ui::SensorForm *ui;
};

#endif // SENSORFORM_H
