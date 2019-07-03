#include "nodeform.h"
#include "ui_nodeform.h"

NodeForm::NodeForm(const QString homeId,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeForm),homeId(homeId)
{
    ui->setupUi(this);
    ui->label_homeName->setText(QString(homeId));
}

NodeForm::~NodeForm()
{
    delete ui;
}
