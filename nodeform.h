#ifndef NODEFORM_H
#define NODEFORM_H

#include <QWidget>

namespace Ui {
class nodeForm;
}

class NodeForm : public QWidget
{
    Q_OBJECT

public:
    explicit NodeForm(QString homeId,QWidget *parent = nullptr);
    ~NodeForm();

private:
    Ui::nodeForm *ui;
    QString homeId;
};

#endif // NODEFORM_H
