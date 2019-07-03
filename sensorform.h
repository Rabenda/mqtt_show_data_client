#ifndef SENSORFORM_H
#define SENSORFORM_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class SensorForm;
}

class SensorForm : public QWidget
{
    Q_OBJECT

signals:
    void switchHome();

private slots:
    void on_buttonbox_clicked(QAbstractButton *button);

public:
    explicit SensorForm(QWidget *parent = nullptr);
    void setHomeId(const QString& homeId);
    ~SensorForm();

private:
    Ui::SensorForm *ui;
    QString homeId;
};

#endif // SENSORFORM_H
