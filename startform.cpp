#include "startform.h"
#include "ui_startform.h"

StartForm::StartForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartForm)
{
    ui->setupUi(this);
}

StartForm::~StartForm()
{
    delete ui;
}
