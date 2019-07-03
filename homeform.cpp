#include "homeform.h"
#include "ui_homeform.h"

HomeForm::HomeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeForm)
{
    ui->setupUi(this);

    model = new QStringListModel();
    ui->listView->setModel(model);
    //model

    connect(ui->button_add,SIGNAL(clicked()),this,SLOT(()),Qt::UniqueConnection);
    connect(ui->button_delete,SIGNAL(clicked()),this,SLOT(on_button_delete_clicked()),Qt::UniqueConnection);
    connect(ui->button_return,SIGNAL(clicked()),this,SLOT(on_button_return_clicked()),Qt::UniqueConnection);
    connect(ui->button_sensorList,SIGNAL(clicked()),this,SLOT(on_button_sensorList_clicked()),Qt::UniqueConnection);
    connect(ui->button_contollerList,SIGNAL(clicked()),this,SLOT(on_button_contollerList_clicked()),Qt::UniqueConnection);
    connect(ui->button_nodeSelect,SIGNAL(clicked()),this,SLOT(on_button_nodeSelect_clicked()),Qt::UniqueConnection);

    connect(ui->listView,SIGNAL(clicked()),this,SLOT(on_listView_clicked()),Qt::UniqueConnection);
}

HomeForm::~HomeForm()
{
    delete ui;
}

void HomeForm::on_button_add_clicked()
{
    int row = model->rowCount();
    QString data;
    data.sprintf("Home%d",row);

    model->insertRow(row);
    model->setData(model->index(row),data);

}
void HomeForm::on_button_delete_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0)
        model->removeRow(modelIndexList.first().row());
    else {
        setButtonDisable();
    }
}

void HomeForm::on_button_return_clicked()
{

}
void HomeForm::on_button_sensorList_clicked()
{

}
void HomeForm::on_button_contollerList_clicked()
{

}
void HomeForm::on_button_nodeSelect_clicked()
{
    QModelIndexList modelIndexList = ui->listView->selectionModel()->selectedIndexes();
    if(modelIndexList.size() > 0) {
        nodeFrom = new NodeForm(modelIndexList.first().data().value<QString>());
        nodeFrom->show();
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
