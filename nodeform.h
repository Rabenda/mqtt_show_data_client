#ifndef NODEFORM_H
#define NODEFORM_H

#include <QWidget>

namespace Ui {
class nodeForm;
}

class nodeForm : public QWidget
{
    Q_OBJECT

public:
    explicit nodeForm(QWidget *parent = nullptr);
    ~nodeForm();

private:
    Ui::nodeForm *ui;
};

#endif // NODEFORM_H
