#include "nodeform.h"
#include "ui_nodeform.h"
#include <QObject>
#include "mosqclientutils.hpp"
#include <QDebug>
#include <QPushButton>

NodeForm::NodeForm(int roomId,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeForm),roomId(roomId)
{
    ui->setupUi(this);
    ui->label_homeName->setText(QString(roomId));
    nonBindingNode = new QStringListModel{};
    ui->list_availableNode->setModel(nonBindingNode);
    bindingNode = new QStringListModel{};
    ui->list_selectedNode->setModel(bindingNode);
    connect(ui->buttonBox,
            &QDialogButtonBox::clicked,
            this,
            &NodeForm::on_buttonbox_clicked,
            Qt::UniqueConnection);

    connect(ui->button_insertSelect,
            &QPushButton::clicked,
            this,
            &NodeForm::on_button_insertSelect_clicked,
            Qt::UniqueConnection);

    connect(ui->button_removeSelect,
            &QPushButton::clicked,
            this,
            &NodeForm::on_button_removeSelect_clicked,
            Qt::UniqueConnection);

    connect(ui->button_removeAll,
            &QPushButton::clicked,
            this,
            &NodeForm::on_button_removeAll_clicked,
            Qt::UniqueConnection);
}

NodeForm::~NodeForm()
{
    delete ui;
}

void NodeForm::setRoomId(int roomId)
{
    this->roomId = roomId;
    QString data;
    data.sprintf("%d", roomId);
    ui->label_homeName->setText(data);
}

void NodeForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        //TODO Update select item
        auto util = MosqClientUtils::getInstance();
        util->updateNodeRoomId(this->roomId, bindingNode->stringList());
        auto inRoomSet = bindingNode->stringList().toSet();
        auto oldInRoomSet = util->selectNodeInRoom(this->roomId);
        oldInRoomSet -= inRoomSet;
        util->updateNodeRoomId(0, QStringList{oldInRoomSet.toList()});
    }
    emit switchHome();
}

void NodeForm::on_button_insertSelect_clicked()
{
    QModelIndexList modelIndexList = ui->list_availableNode->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        bindingNode->insertRow(bindingNode->rowCount(),modelIndexList.first());
        nonBindingNode->removeRow(modelIndexList.first().row());
    }
}

void NodeForm::on_button_removeSelect_clicked()
{
    QModelIndexList modelIndexList = ui->list_availableNode->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        nonBindingNode->insertRow(nonBindingNode->rowCount(),modelIndexList.first());
        bindingNode->removeRow(modelIndexList.first().row());
    }
}

void NodeForm::on_button_removeAll_clicked()
{
    for (int i = 0;i < bindingNode->rowCount(); i++) {
        nonBindingNode->insertRow(nonBindingNode->rowCount(),bindingNode->index(i));
        bindingNode->removeRow(i);
    }
}

void NodeForm::refreshNonBindingNode() {
    auto row = nonBindingNode->rowCount();
    nonBindingNode->removeRows(0, row);
    auto util = MosqClientUtils::getInstance();
    auto nodeList = util->selectNodeNotInRoom(this->roomId);
    qDebug() << nodeList;
    for (auto const& node: nodeList) {
        row = nonBindingNode->rowCount();
        nonBindingNode->insertRow(row);
        nonBindingNode->setData(nonBindingNode->index(row), node);
    }
}

void NodeForm::refreshBindingNode() {
    auto row = bindingNode->rowCount();
    bindingNode->removeRows(0, row);
    auto util = MosqClientUtils::getInstance();

    auto nodeList = util->selectNodeInRoom(this->roomId);
    qDebug() << nodeList;
    for (auto const& node: nodeList) {
        row = bindingNode->rowCount();
        bindingNode->insertRow(row);
        bindingNode->setData(bindingNode->index(row), node);
    }
}

void NodeForm::refresh() {
    refreshNonBindingNode();
    refreshBindingNode();
}
