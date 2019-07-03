#ifndef VALSETFORM_H
#define VALSETFORM_H

#include <QWidget>

namespace Ui {
class ValSetForm;
}

class ValSetForm : public QWidget
{
    Q_OBJECT

public:
    explicit ValSetForm(QWidget *parent = nullptr);
    ~ValSetForm();

private:
    Ui::ValSetForm *ui;
};

#endif // VALSETFORM_H
