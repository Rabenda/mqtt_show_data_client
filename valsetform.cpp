#include "valsetform.h"
#include "ui_valsetform.h"
#include <QString>
#include "mosqclientutils.hpp"
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

void ValSetForm::refresh()
{
    QString str;
    str.sprintf("%d",roomId);
    ui->label_home->setText(str);
    ui->label_id->setText(contro.id);
    ui->label_type->setText(contro.type);
}

void ValSetForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        this->helperUpdateControllerData();
    }
    emit switchContro();
}

void ValSetForm::on_pushButton_clicked()
{
    this->helperUpdateControllerData();
}

void ValSetForm::helperUpdateControllerData()
{
    auto util = MosqClientUtils::getInstance();
    util->updateControllerValue(this->contro);
}
