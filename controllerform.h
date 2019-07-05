#ifndef CONTROLLERFORM_H
#define CONTROLLERFORM_H

#include <QWidget>
#include <QAbstractButton>
#include <QStandardItemModel>
#include "mostype.h"

namespace Ui {
class ControllerForm;
}

class ControllerForm : public QWidget
{
    Q_OBJECT

signals:
    void switchHome();
    void switchValSet(int roomId,Controller contro);

private slots:
    void on_buttonbox_clicked(QAbstractButton *button);
    void on_button_setVal_clicked();

public:
    explicit ControllerForm(QWidget *parent = nullptr);
    void setRoomId(int roomId);
    ~ControllerForm();
    void refresh() {refreshData();}

private:
    Ui::ControllerForm* ui;
    QStandardItemModel* model;
    int roomId;
    void refreshData();
};

#endif // CONTROLLERFORM_H
