#include "nodeform.h"
#include "ui_nodeform.h"
#include <QObject>
#include "mosqclientutils.hpp"

NodeForm::NodeForm(int homeId,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeForm),homeId(homeId)
{
    ui->setupUi(this);
    ui->label_homeName->setText(QString(homeId));
    nonBindingNode = new QStringListModel{};
    ui->list_availableNode->setModel(nonBindingNode);
    bindingNode = new QStringListModel{};
    ui->list_selectedNode->setModel(nonBindingNode);
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
}

NodeForm::~NodeForm()
{
    delete ui;
}

void NodeForm::setHomeId(int homeId)
{
    this->homeId = homeId;
    QString data;
    data.sprintf("%d", homeId);
    ui->label_homeName->setText(data);
}

void NodeForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        //TODO Update select item
        auto util = MosqClientUtils::getInstance();
        util->updateNodeRoomId(this->homeId, bindingNode->stringList());
        auto inRoomSet = bindingNode->stringList().toSet();
        auto oldInRoomSet = util->selectNodeInRoom(this->homeId);
        oldInRoomSet -= inRoomSet;
        util->updateNodeRoomId(0, QStringList{oldInRoomSet.toList()});
    }
    emit switchHome();
}

void NodeForm::refreshNonBindingNode() {
    auto row = nonBindingNode->rowCount();
    nonBindingNode->removeRows(0, row);
    auto util = MosqClientUtils::getInstance();
    auto nodeList = util->selectNodeNotInRoom(this->homeId);

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

    auto nodeList = util->selectNodeInRoom(this->homeId);

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
