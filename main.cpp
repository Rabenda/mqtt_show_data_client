#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <mosqclient.hpp>
#include <QtGlobal>

#include <string>
#include <QString>
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
//    QByteArray b = QString("2.0").toStdString().c_str();
//    qputenv("QT_SCALE_FACTOR", b);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    MosqClient mosqClient("233","2", "127.0.0.1", 1883);
    mosqClient.send_message("hello233");
    return app.exec();
}
