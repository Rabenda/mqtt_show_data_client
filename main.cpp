#include <QApplication>
#include <QtGlobal>
#include <QObject>
#include <QString>
#include "mosqclient.hpp"
#include "mainwindow.h"
#define FONT_SIZE 72

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    auto mosqClient = MosqClient::getInstance();
    mosqClient->send_message("ControlData", "hello233");
    auto font = QFont("", FONT_SIZE);
    app.setFont(font);
    return app.exec();
}
