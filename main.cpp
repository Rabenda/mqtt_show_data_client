#include <QApplication>

#include <mosqclient.hpp>
#include <QtGlobal>
#include "mainwindow.h"
#include <QObject>

#include <string>
#include <QString>
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
