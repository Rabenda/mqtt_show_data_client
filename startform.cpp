#include "startform.h"
#include "ui_startform.h"
#include <QObject>

StartForm::StartForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartForm)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()),Qt::UniqueConnection);
}

StartForm::~StartForm()
{
    delete ui;
}

void StartForm::on_pushButton_clicked()
{
    emit switchHome();
}
