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
    void switchNode(int homeId);
    void switchSensor(int homeId);
    void switchContro(int homeId);

public:

    //MainWindow* main;
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
    QStringListModel *model;
    Ui::HomeForm *ui;
    NodeForm* nodeFrom;

    void setButtonDisable();
};

#endif // HOMEFORM_H
