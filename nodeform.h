#ifndef NODEFORM_H
#define NODEFORM_H

#include <QWidget>
#include <QAbstractButton>
#include <QStringListModel>
namespace Ui {
class nodeForm;
}

class NodeForm : public QWidget
{
    Q_OBJECT

signals:
    void switchHome();

private slots:
    void on_buttonbox_clicked(QAbstractButton *button);
    void on_button_insertSelect_clicked();
    void on_button_removeSelect_clicked();
    void on_button_removeAll_clicked();

public:
    explicit NodeForm(int roomId = 0,QWidget *parent = nullptr);
    void setRoomId(int roomId);
    void refresh();

    ~NodeForm();
private:
    Ui::nodeForm* ui;
    QStringListModel* nonBindingNode;
    QStringListModel* bindingNode;
    int roomId;
    void refreshBindingNode();
    void refreshNonBindingNode();
};

#endif // NODEFORM_H
