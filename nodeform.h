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


public:
    explicit NodeForm(int homeId = 0,QWidget *parent = nullptr);
    void setHomeId(int homeId);
    void refresh();

    ~NodeForm();


private:
    Ui::nodeForm *ui;
    QStringListModel* nonBindingNode;
    QStringListModel* bindingNode;
    int homeId;
    void refreshBindingNode();
    void refreshNonBindingNode();
};

#endif // NODEFORM_H
