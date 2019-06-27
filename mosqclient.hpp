#ifndef MOSQCLIENT_HPP
#define MOSQCLIENT_HPP

#include <mosquitto.h>
#include <string>
#include <QObject>
#include <QString>

constexpr int QOS_0 = 0;
constexpr int QOS_1 = 1;
constexpr int QOS_2 = 2;
#define HOST "127.0.0.1"
constexpr int16_t PORT = 1883;
class MosqClient: public QObject
{
    Q_OBJECT
private:
    std::string id;
    int keepalive;
    mosquitto *mosq;
public:
    MosqClient(std::string const& id);
    ~MosqClient();
    bool send_message(std::string const& message);
};

#endif // MOSQCLIENT_HPP
