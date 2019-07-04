#ifndef HOMEFORM_H
#define HOMEFORM_H

#include <QWidget>
#include <QStringListModel>
#include "nodeform.h"

namespace Ui {
class HomeForm;
}

class HomeForm : public QWidget
{
    Q_OBJECT

signals:
    void switchStart();
    void switchNode(int roomId);
    void switchSensor(int roomId);
    void switchContro(int roomId);

public:
    explicit HomeForm(QWidget *parent = nullptr);
    ~HomeForm();

    void refresh();

private slots:
    void on_button_add_clicked();
    void on_button_delete_clicked();
    void on_button_return_clicked();
    void on_button_sensorList_clicked();
    void on_button_contollerList_clicked();
    void on_button_nodeSelect_clicked();

    void on_listView_clicked();
    void listViewInsert(int index);
private:
    QStringListModel* model;
    Ui::HomeForm* ui;
    NodeForm* nodeFrom;

    void setButtonDisable();
};

#endif // HOMEFORM_H
