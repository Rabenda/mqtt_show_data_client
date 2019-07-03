#ifndef NODEFORM_H
#define NODEFORM_H

#include <QWidget>
#include <QAbstractButton>

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
    explicit NodeForm(QString homeId = "",QWidget *parent = nullptr);
    void setHomeId(const QString& homeId);

    ~NodeForm();

private:
    QString homeId;
    Ui::nodeForm *ui;
};

#endif // NODEFORM_H
