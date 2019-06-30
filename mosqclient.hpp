#ifndef MOSQCLIENT_HPP
#define MOSQCLIENT_HPP

#include <mosquitto.h>
#include <QObject>
#include <QString>
#include <QMutex>
#include <QMutexLocker>

constexpr int QOS_0 = 0;
constexpr int QOS_1 = 1;
constexpr int QOS_2 = 2;
#define HOST "127.0.0.1"
constexpr int16_t PORT = 1883;
class MosqClient: public QObject
{
    Q_OBJECT
private:
    QString id;
    int keepalive;
    mosquitto *mosq;
    static MosqClient* instance;
    MosqClient(QString const& id);
public:
    static MosqClient* getInstance();
    static QMutex mutex;
    ~MosqClient();
    bool send_message(QString const& topic, QString const& message);
};

#endif // MOSQCLIENT_HPP
