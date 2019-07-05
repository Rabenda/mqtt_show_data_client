#include "homeform.h"
#include "ui_homeform.h"
#include "mosqclientutils.hpp"

HomeForm::HomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeForm)
{
    ui->setupUi(this);

    model = new QStringListModel();
    ui->listView->setModel(model);
    //model

//    connect(ui->button_add,&QPushButton::clicked,
//            this,&HomeForm::on_button_add_clicked,Qt::UniqueConnection);
//    connect(ui->button_delete,&QPushButton::clicked,
//            this,&HomeForm::on_button_delete_clicked,Qt::UniqueConnection);
    connect(ui->button_return,&QPushButton::clicked,
            this,&HomeForm::on_button_return_clicked,Qt::UniqueConnection);
    connect(ui->button_sensorList,&QPushButton::clicked,
            this,&HomeForm::on_button_sensorList_clicked,Qt::UniqueConnection);
    connect(ui->button_contollerList,&QPushButton::clicked,
            this,&HomeForm::on_button_contollerList_clicked,Qt::UniqueConnection);
    connect(ui->button_nodeSelect,&QPushButton::clicked,
            this,&HomeForm::on_button_nodeSelect_clicked,Qt::UniqueConnection);

    connect(ui->listView,&QListView::clicked,
            this,&HomeForm::on_listView_clicked,Qt::UniqueConnection);
}

HomeForm::~HomeForm()
{
    delete ui;
}

void HomeForm::listViewInsert(int index) {
    QString data;
    data.sprintf("%d", index);
    auto row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row),data);
}

void HomeForm::refresh() {
    auto row = model->rowCount();
    model->removeRows(0, row);

    auto util = MosqClientUtils::getInstance();
    auto indexs = util->selectRoomId();
    for (auto const& index: indexs) {
        listViewInsert(index);
    }
}

void HomeForm::on_button_add_clicked()
{
    auto util = MosqClientUtils::getInstance();

    int index = util->getNextRoomId();
    listViewInsert(index);
    util->helperUpdateRoomId(index);
}
void HomeForm::on_button_delete_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();

    if(modelIndexList.size() > 0) {
        auto roomId = modelIndexList.first().data().toInt();
        model->removeRow(modelIndexList.first().row());

        auto util = MosqClientUtils::getInstance();
        util->deleteRoomId(roomId);
    }
    else {
        setButtonDisable();
    }
}

void HomeForm::on_button_return_clicked()
{
    emit switchStart();
}
void HomeForm::on_button_sensorList_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        emit switchSensor(modelIndexList.first().data().toInt());
    }
    else {
        setButtonDisable();
    }
}
void HomeForm::on_button_contollerList_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        emit switchContro(modelIndexList.first().data().toInt());
    }
    else {
        setButtonDisable();
    }
}
void HomeForm::on_button_nodeSelect_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        emit switchNode(modelIndexList.first().data().toInt());
    }
    else {
        setButtonDisable();
    }
}

void HomeForm::on_listView_clicked()
{
    //this->disconnect(SLOT(on_listView_clicked()));
    ui->button_delete->setEnabled(true);
    ui->button_sensorList->setEnabled(true);
    ui->button_contollerList->setEnabled(true);
    ui->button_nodeSelect->setEnabled(true);
}

void HomeForm::setButtonDisable()
{
    ui->button_delete->setEnabled(false);
    ui->button_sensorList->setEnabled(false);
    ui->button_contollerList->setEnabled(false);
    ui->button_nodeSelect->setEnabled(false);
}
