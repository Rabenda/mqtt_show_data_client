#ifndef CONTROLLERFORM_H
#define CONTROLLERFORM_H

#include <QWidget>

namespace Ui {
class ControllerForm;
}

class ControllerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerForm(QWidget *parent = nullptr);
    ~ControllerForm();

private:
    Ui::ControllerForm *ui;
};

#endif // CONTROLLERFORM_H
