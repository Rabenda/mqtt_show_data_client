#include "controllerform.h"
#include "ui_controllerform.h"
#include <QList>
#include "mosqclientutils.hpp"

ControllerForm::ControllerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerForm)
{
    ui->setupUi(this);

    model = new QStandardItemModel;
    model->setColumnCount(3);
    model->setHeaderData(0,Qt::Horizontal,QString("id"));
    model->setHeaderData(1,Qt::Horizontal,QString("type"));
    model->setHeaderData(2,Qt::Horizontal,QString("data"));

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->horizontalHeader()->setSectionsMovable(false);

    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,98);

    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
    connect(ui->button_setVal,SIGNAL(clicked()),this,SLOT(on_button_setVal_clicked()),Qt::UniqueConnection);
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

void ControllerForm::setRoomId(int roomId)
{
    this->roomId = roomId;
    QString data;
    data.sprintf("%d", roomId);
    ui->label_home->setText(data);
}

void ControllerForm::refreshData()
{
    model->removeRows(0, model->rowCount());

    auto util = MosqClientUtils::getInstance();
    auto controllerDataList = util->selectControllerFromRoomId(this->roomId);
    for (int i = 0; i < controllerDataList.length(); ++i) {
        auto const& controller = controllerDataList[i];
        QString data;
        data.sprintf("%d", controller.data);
        model->setItem(i,0,new QStandardItem(controller.id));
        model->setItem(i,1,new QStandardItem(controller.type));
        model->setItem(i,2,new QStandardItem(data));
    }
}

void ControllerForm::on_button_setVal_clicked()
{
    QModelIndexList modelIndexList = ui->tableView->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        Controller contro;
        int row = modelIndexList.first().row();
        contro.id = model->index(row,0).data().value<QString>();
        contro.type = model->index(row,1).data().value<QString>();
        contro.data = model->index(row,2).data().toInt();
        emit switchValSet(roomId,contro);
    }
}

