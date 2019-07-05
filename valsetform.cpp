#include "valsetform.h"
#include "ui_valsetform.h"
#include <QString>
#include "mosqclientutils.hpp"
#include "mosqclient.hpp"
#include <QDial>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
ValSetForm::ValSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValSetForm)
{
    ui->setupUi(this);

    connect(ui->dial,&QDial::valueChanged,
            this,&ValSetForm::on_dial_changed);

    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),
            this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
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
    ui->dial->setValue(contro.data);
}

void ValSetForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        this->helperUpdateControllerData();
    }
    emit switchContro(this->roomId);
}

void ValSetForm::on_pushButton_clicked()
{
    this->helperUpdateControllerData();
}

void ValSetForm::helperUpdateControllerData()
{
    auto util = MosqClientUtils::getInstance();
    util->updateControllerValue(this->contro);

    auto json = QString{
            "{\"controller\":[{\"controllerId\":\"%1\",\"controllerVal\":%2}]}"
    }.arg(contro.id).arg(contro.data);
    qDebug() << "json: " << json;
    auto mosqClient = MosqClient::getInstance();
    auto topic = QString{"ControllerData-%1"}.arg(contro.id.split(':').first());
    qDebug() << "topic: " << topic;
    mosqClient->send_message(topic, json);
}

void ValSetForm::on_dial_changed(int value)
{
    QString str;
    str.sprintf("%d",value);
    ui->label_val->setText(str);
    contro.data = value;
}
