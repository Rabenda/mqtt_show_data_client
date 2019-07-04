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

    connect(&startFrom,SIGNAL(switchHome()),this,SLOT(stack_change_homeForm()));//start form -> push >>
    connect(&homeForm,SIGNAL(switchStart()),this,SLOT(stack_change_startFrom()));//home form -> push return
    connect(&homeForm,SIGNAL(switchNode(QString)),this,SLOT(stack_change_nodeForm(QString)));//home form -> push nodes
    connect(&homeForm,SIGNAL(switchSensor(QString)),this,SLOT(stack_change_sensorForm(QString)));//home form -> push sensor
    connect(&homeForm,SIGNAL(switchContro(QString)),this,SLOT(stack_change_controllerForm(QString)));//home form -> push contro

    connect(&nodeForm,SIGNAL(switchHome()),this,SLOT(stack_change_homeForm()));//node form -> push ok/cancle

    connect(&sensorForm,SIGNAL(switchHome()),this,SLOT(stack_change_homeForm()));//sensor form -> push ok/cancle

    connect(&controllerForm,SIGNAL(switchHome()),this,SLOT(stack_change_homeForm()));//sensor form -> push ok/cancle

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
}
void MainWindow::stack_change_nodeForm(QString homeId)
{
    nodeForm.setHomeId(homeId);
    ui->stackedLayout->setCurrentWidget(&nodeForm);
}
void MainWindow::stack_change_sensorForm(QString homeId)
{
    sensorForm.setHomeId(homeId);
    ui->stackedLayout->setCurrentWidget(&sensorForm);
}
void MainWindow::stack_change_controllerForm(QString homeId)
{
    controllerForm.setHomeId(homeId);
    ui->stackedLayout->setCurrentWidget(&controllerForm);
}
void MainWindow::stack_change_setValForm(controller contro)
{

}
