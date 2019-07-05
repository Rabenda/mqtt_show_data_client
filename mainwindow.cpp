#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedLayout->addWidget(&startFrom);
    ui->stackedLayout->addWidget(&homeForm);
    ui->stackedLayout->addWidget(&nodeForm);
    ui->stackedLayout->addWidget(&sensorForm);
    ui->stackedLayout->addWidget(&controllerForm);
    ui->stackedLayout->addWidget(&valSetForm);

    connect(&startFrom,&StartForm::switchHome,
            this,&MainWindow::stack_change_homeForm);//start form -> push >>
    connect(&homeForm,&HomeForm::switchStart,
            this,&MainWindow::stack_change_startFrom);//home form -> push return
    connect(&homeForm,&HomeForm::switchNode,
            this,&MainWindow::stack_change_nodeForm);//home form -> push nodes
    connect(&homeForm,&HomeForm::switchSensor,
            this,&MainWindow::stack_change_sensorForm);//home form -> push sensor
    connect(&homeForm,&HomeForm::switchContro,
            this,&MainWindow::stack_change_controllerForm);//home form -> push contro
    connect(&nodeForm,&NodeForm::switchHome,
            this,&MainWindow::stack_change_homeForm);//node form -> push ok/cancle
    connect(&sensorForm,&SensorForm::switchHome,
            this,&MainWindow::stack_change_homeForm);//sensor form -> push ok/cancle
    connect(&controllerForm,&ControllerForm::switchHome,
            this,&MainWindow::stack_change_homeForm);//sensor form -> push ok/cancle

    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::stack_change_startFrom()
{
    ui->stackedLayout->setCurrentWidget(&startFrom);
}
void MainWindow::stack_change_homeForm()
{
    ui->stackedLayout->setCurrentWidget(&homeForm);
    homeForm.refresh();
}
void MainWindow::stack_change_nodeForm(int roomId)
{
    nodeForm.setRoomId(roomId);
    ui->stackedLayout->setCurrentWidget(&nodeForm);
    nodeForm.refresh();
}
void MainWindow::stack_change_sensorForm(int roomId)
{
    sensorForm.setRoomId(roomId);
    ui->stackedLayout->setCurrentWidget(&sensorForm);
    sensorForm.refresh();
}
void MainWindow::stack_change_controllerForm(int roomId)
{
    controllerForm.setRoomId(roomId);
    ui->stackedLayout->setCurrentWidget(&controllerForm);
    controllerForm.refresh();
}
void MainWindow::stack_change_setValForm(Controller contro)
{
    Q_UNUSED(contro)
}
