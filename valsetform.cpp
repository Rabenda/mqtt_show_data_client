#include "valsetform.h"
#include "ui_valsetform.h"

ValSetForm::ValSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValSetForm)
{
    ui->setupUi(this);
}

ValSetForm::~ValSetForm()
{
    delete ui;
}
