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
    void setRoomId(int roomId);
    ~ControllerForm();

private:
    Ui::ControllerForm* ui;
    QStandardItemModel* model;
    int roomId;
    void refreshData();
};

#endif // CONTROLLERFORM_H
