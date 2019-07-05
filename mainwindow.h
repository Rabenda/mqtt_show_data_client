#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "startform.h"
#include "homeform.h"
#include "nodeform.h"
#include "sensorform.h"
#include "controllerform.h"
#include "valsetform.h"
#include "mostype.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void stack_change_startFrom();
    void stack_change_homeForm();
    void stack_change_nodeForm(int roomId);
    void stack_change_sensorForm(int roomId);
    void stack_change_controllerForm(int roomId);
    void stack_change_setValForm(int roomId,Controller contro);

private:
    Ui::MainWindow *ui;

    StartForm startFrom;
    HomeForm homeForm;
    NodeForm nodeForm;
    SensorForm sensorForm;
    ControllerForm controllerForm;
    ValSetForm valSetForm;
};

#endif // MAINWINDOW_H
