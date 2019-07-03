#include "controllerform.h"
#include "ui_controllerform.h"

ControllerForm::ControllerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerForm)
{
    ui->setupUi(this);
}

ControllerForm::~ControllerForm()
{
    delete ui;
}
