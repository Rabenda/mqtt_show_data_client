#ifndef VALSETFORM_H
#define VALSETFORM_H

#include <QWidget>
#include <QAbstractButton>
#include "mostype.h"

namespace Ui {
class ValSetForm;
}

class ValSetForm : public QWidget
{
    Q_OBJECT

signals:
    void switchContro();

private slots:
    void on_buttonbox_clicked(QAbstractButton *button);

public:
    int roomId;
    Controller contro;

    explicit ValSetForm(QWidget *parent = nullptr);
    void refresh();
    ~ValSetForm();

private:
    Ui::ValSetForm *ui;
};

#endif // VALSETFORM_H
