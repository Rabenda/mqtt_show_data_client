#include "mainwindow.hpp"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()),Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    homeFrom.show();
    connect(&homeFrom,SIGNAL(destroyed()),this,SLOT(on_homeFrom_destroyed()),Qt::UniqueConnection);
}

void MainWindow::on_homeFrom_destroyed()
{
    this->show();
}
