#include "nodeform.h"
#include "ui_nodeform.h"
#include <QObject>
#include "mosqclientutils.hpp"

NodeForm::NodeForm(int roomId,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeForm),roomId(roomId)
{
    ui->setupUi(this);
    ui->label_homeName->setText(QString(roomId));
    nonBindingNode = new QStringListModel{};
    ui->list_availableNode->setModel(nonBindingNode);
    bindingNode = new QStringListModel{};
    ui->list_selectedNode->setModel(nonBindingNode);
    connect(ui->buttonBox,
            &QDialogButtonBox::clicked,
            this,
            &NodeForm::on_buttonbox_clicked,
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

void NodeForm::refreshNonBindingNode() {
    auto row = nonBindingNode->rowCount();
    nonBindingNode->removeRows(0, row);
    auto util = MosqClientUtils::getInstance();
    auto nodeList = util->selectNodeNotInRoom(this->roomId);

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
