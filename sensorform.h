#ifndef SENSORFORM_H
#define SENSORFORM_H

#include <QWidget>
#include <QAbstractButton>
#include <QStandardItemModel>

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
    void on_button_refresh_clicked();

public:
    QStandardItemModel  *model;

    explicit SensorForm(QWidget *parent = nullptr);
    void setHomeId(int homeId);
    ~SensorForm();

private:
    Ui::SensorForm *ui;
    int homeId;

    void refreshData();
};

#endif // SENSORFORM_H
