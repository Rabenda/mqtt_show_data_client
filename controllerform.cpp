#include "controllerform.h"
#include "ui_controllerform.h"
#include <QList>

ControllerForm::ControllerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerForm)
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
}

ControllerForm::~ControllerForm()
{
    delete ui;
}

void ControllerForm::on_buttonbox_clicked(QAbstractButton *button)
{
    button->text();
    emit switchHome();
}

void ControllerForm::setHomeId(const QString& homeId)
{
    this->homeId = homeId;
    ui->label_home->setText(homeId);
}

void ControllerForm::refreshData()
{
    model->setItem(0,0,new QStandardItem("1"));
    model->setItem(0,1,new QStandardItem("fan"));
    model->setItem(0,2,new QStandardItem("180"));

    model->setItem(1,0,new QStandardItem("2"));
    model->setItem(1,1,new QStandardItem("light"));
    model->setItem(1,2,new QStandardItem("12.5"));

    model->setItem(2,0,new QStandardItem("3"));
    model->setItem(2,1,new QStandardItem("curtain"));
    model->setItem(2,2,new QStandardItem("0"));
}

