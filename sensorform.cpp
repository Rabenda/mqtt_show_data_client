#include "sensorform.h"
#include "ui_sensorform.h"

SensorForm::SensorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorForm)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton *)),this,SLOT(on_buttonbox_clicked(QAbstractButton *)),Qt::UniqueConnection);
}

SensorForm::~SensorForm()
{
    delete ui;
}

void SensorForm::on_buttonbox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == button)
    {
        //TODO Update select item
    }
    emit switchHome();
}

void SensorForm::setHomeId(const QString& homeId)
{
    this->homeId = homeId;
    ui->label_home->setText(homeId);
}
