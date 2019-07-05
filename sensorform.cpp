#include "sensorform.h"
#include "ui_sensorform.h"
#include "mosqclientutils.hpp"
#include <QString>

SensorForm::SensorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorForm)
{
    ui->setupUi(this);
    model = new QStandardItemModel;
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString("id"));
    model->setHeaderData(1,Qt::Horizontal,QString("type"));
    model->setHeaderData(2,Qt::Horizontal,QString("val"));

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->horizontalHeader()->setSectionsMovable(false);

    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,98);

    refreshData();

    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
    connect(ui->button_refresh,SIGNAL(clicked()),this,SLOT(on_button_refresh_clicked()),Qt::UniqueConnection);
}

SensorForm::~SensorForm()
{
    delete ui;
}

void SensorForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        //TODO Update select item
    }
    emit switchHome();
}

void SensorForm::on_button_refresh_clicked()
{
    refreshData();

    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,98);
}

void SensorForm::setRoomId(int roomId)
{
    this->roomId = roomId;
    QString data;
    data.sprintf("%d", roomId);
    ui->label_home->setText(data);
}

void SensorForm::refreshData()
{
    model->removeRows(0, model->rowCount());

    auto util = MosqClientUtils::getInstance();
    auto sensorDataList = util->selectSensorFromRoomId(this->roomId);
    for (int i = 0; i < sensorDataList.length(); ++i) {
        auto const& sensor = sensorDataList[i];
        QString data;
        data.sprintf("%lf", sensor.data);
        model->setItem(i,0,new QStandardItem(sensor.id));
        model->setItem(i,1,new QStandardItem(sensor.type));
        model->setItem(i,2,new QStandardItem(data));
    }
}
