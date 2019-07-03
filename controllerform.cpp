#include "controllerform.h"
#include "ui_controllerform.h"

ControllerForm::ControllerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControllerForm)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
}

ControllerForm::~ControllerForm()
{
    delete ui;
}

void ControllerForm::on_buttonbox_clicked(QAbstractButton *button)
{
    emit switchHome();
}

void ControllerForm::setHomeId(const QString& homeId)
{
    this->homeId = homeId;
    ui->label_home->setText(homeId);
}
