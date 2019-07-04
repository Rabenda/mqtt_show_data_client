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
    connect(&homeForm,SIGNAL(switchNode(int)),this,SLOT(stack_change_nodeForm(int)));//home form -> push nodes
    connect(&homeForm,SIGNAL(switchSensor(int)),this,SLOT(stack_change_sensorForm(int)));//home form -> push sensor
    connect(&homeForm,SIGNAL(switchContro(int)),this,SLOT(stack_change_controllerForm(int)));//home form -> push contro

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
    homeForm.refresh();
}
void MainWindow::stack_change_nodeForm(int homeId)
{
    nodeForm.setHomeId(homeId);
    ui->stackedLayout->setCurrentWidget(&nodeForm);
    nodeForm.refresh();
}
void MainWindow::stack_change_sensorForm(int homeId)
{
    sensorForm.setHomeId(homeId);
    ui->stackedLayout->setCurrentWidget(&sensorForm);
}
void MainWindow::stack_change_controllerForm(int homeId)
{
    controllerForm.setHomeId(homeId);
    ui->stackedLayout->setCurrentWidget(&controllerForm);
}
void MainWindow::stack_change_setValForm(controller contro)
{

}
