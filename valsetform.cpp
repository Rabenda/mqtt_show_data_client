#include "valsetform.h"
#include "ui_valsetform.h"
#include <QString>

ValSetForm::ValSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValSetForm)
{
    ui->setupUi(this);

    connect(ui->dial,SIGNAL(valueChanged()),this,SLOT(on_dial_changed()));
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
    Q_UNUSED(button)
}

void ValSetForm::on_dial_changed()
{
    QString str;
    str.sprintf("%d",ui->dial->value());
    ui->label_val->setText(str);
    contro.data = ui->dial->value();
}
