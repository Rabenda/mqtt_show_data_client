#ifndef CONTROLLERFORM_H
#define CONTROLLERFORM_H

#include <QWidget>
#include <QAbstractButton>
#include <QStandardItemModel>

namespace Ui {
class ControllerForm;
}

class ControllerForm : public QWidget
{
    Q_OBJECT

signals:
    void switchHome();

private slots:
    void on_buttonbox_clicked(QAbstractButton *button);

public:
    explicit ControllerForm(QWidget *parent = nullptr);
    void setHomeId(const QString& homeId);
    ~ControllerForm();

private:
    QStandardItemModel  *model;

    Ui::ControllerForm *ui;
    QString homeId;

    void refreshData();
};

#endif // CONTROLLERFORM_H
