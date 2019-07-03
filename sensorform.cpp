#include "sensorform.h"
#include "ui_sensorform.h"

SensorForm::SensorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorForm)
{
    ui->setupUi(this);
}

SensorForm::~SensorForm()
{
    delete ui;
}
