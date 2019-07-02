#include "nodeform.h"
#include "ui_nodeform.h"

nodeForm::nodeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeForm)
{
    ui->setupUi(this);
}

nodeForm::~nodeForm()
{
    delete ui;
}
