#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDialog>

#include "homeform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_homeFrom_destroyed();

private:
    Ui::MainWindow *ui;
    HomeForm homeFrom;
};

#endif // MAINWINDOW_HPP
