#include "sensorform.h"
#include "ui_sensorform.h"

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

void SensorForm::setHomeId(int homeId)
{
    this->homeId = homeId;
    QString data;
    data.sprintf("%d", homeId);
    ui->label_home->setText(data);
}

void SensorForm::refreshData()
{
    model->setItem(0,0,new QStandardItem("1"));
    model->setItem(0,1,new QStandardItem("light"));
    model->setItem(0,2,new QStandardItem("12.5"));


    model->setItem(1,0,new QStandardItem("2"));
    model->setItem(1,1,new QStandardItem("DHT11_T"));
    model->setItem(1,2,new QStandardItem("0"));

    model->setItem(2,0,new QStandardItem("2"));
    model->setItem(2,1,new QStandardItem("DHT11_H"));
    model->setItem(2,2,new QStandardItem("0"));
}
