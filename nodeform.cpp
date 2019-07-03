#include "nodeform.h"
#include "ui_nodeform.h"
#include <QObject>

NodeForm::NodeForm(const QString homeId,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeForm),homeId(homeId)
{
    ui->setupUi(this);
    ui->label_homeName->setText(QString(homeId));
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
}

NodeForm::~NodeForm()
{
    delete ui;
}

void NodeForm::setHomeId(const QString& homeId)
{
    this->homeId = homeId;
    ui->label_homeName->setText(homeId);
}

void NodeForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        //TODO Update select item
    }
    emit switchHome();
}
