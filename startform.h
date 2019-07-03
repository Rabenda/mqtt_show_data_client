#ifndef STARTFORM_H
#define STARTFORM_H

#include <QWidget>

namespace Ui {
class StartForm;
}

class StartForm : public QWidget
{
    Q_OBJECT

signals:
    void switchHome();

public:
    explicit StartForm(QWidget *parent = nullptr);
    ~StartForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::StartForm *ui;
};

#endif // STARTFORM_H
