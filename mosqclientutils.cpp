#include "mosqclientutils.hpp"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValueRef>
#include "mosqclient.hpp"

MosqClientUtils* MosqClientUtils::instance = nullptr;
QMutex MosqClientUtils::mutex;

MosqClientUtils* MosqClientUtils::getInstance() {
    QMutexLocker locker(&mutex);
    if (instance == nullptr) {
        instance = new MosqClientUtils;
    }
    return instance;
}

MosqClientUtils::MosqClientUtils(QObject *parent) : QObject(parent)
{

// "create table room(roomId int primary key AUTOINCREMENT)
// "create table node(id char(20) primary key, roomId char(20),status int)"
// "create table controller(id char(20) primary key, type char(20), data float)"
// "create table sensor(id char(20) primary key, type char(20), data float)"

    QSqlQuery query{};
    auto tableRoomCreateSql = "CREATE TABLE IF NOT EXISTS room(roomId int primary key)";
    if (!query.exec(tableRoomCreateSql)) {
        qDebug() << "Database table Room create failed: " << query.lastError();
    } else {
        qDebug() << "Database table Room create sucessful";
    }

    auto tableNodeCreateSql = "CREATE TABLE IF NOT EXISTS node(id char(20) primary key, roomId int ,status int)";
    if (!query.exec(tableNodeCreateSql)) {
        qDebug() << "Database table Node create failed: " << query.lastError();
    } else {
        qDebug() << "Database table Node create sucessful";
    }

    auto tableControllerCreateSql = "CREATE TABLE IF NOT EXISTS controller(id char(20) primary key, type char(20), data float)";
    if (!query.exec(tableControllerCreateSql)) {
        qDebug() << "Database table controller create failed: " << query.lastError();
    } else {
        qDebug() << "Database table controller create sucessful";
    }

    auto tableSensorCreateSql = "CREATE TABLE IF NOT EXISTS sensor(id char(20) primary key, type char(20), data float)";
    if (!query.exec(tableSensorCreateSql)) {
        qDebug() << "Database table sensor create failed: " << query.lastError();
    } else {
        qDebug() << "Database table sensor create sucessful";
    }
}

void MosqClientUtils::helperDealWithOnlineNode(QJsonDocument const& json){

    auto data = json["nodeId"].toString();
    if (data == "")
        return;
    auto updateTableOnlineNodeSql =
            QString("INSERT OR REPLACE INTO node(id, status) VALUES (\"%1\", 1)").arg(data);

    auto requestName = QString("RequestUpdateNode-%1").arg(data);

    auto mosqClient = MosqClient::getInstance();
    mosqClient->send_message(requestName, "None");

    qDebug() << "updateTableOnlineNodeSql : " << updateTableOnlineNodeSql;
    QSqlQuery query{};
    if (!query.exec(updateTableOnlineNodeSql)) {
        qDebug() << "Database table node insert failed: " << query.lastError();
    } else {
        qDebug() << "Database table node insert sucessful";
    }
}

void MosqClientUtils::helperDealWithUpdateNode(QJsonDocument const& json){
    auto nodeId = json["nodeId"].toString();
    auto sensorArray = json["sensor"].toArray();
    auto controllerArray = json["controller"].toArray();
    auto updateTableSensorSql =
            QString("INSERT OR REPLACE INTO sensor(id, type) VALUES (\"%1\", \"%2\")");

    QSqlQuery query{};
    for (auto sensor: sensorArray) {
        auto sensorJsonMap = sensor.toObject();
        auto type = sensorJsonMap["type"].toString();
        auto sensorId = sensorJsonMap["sensorId"].toString();
        auto updateTableSensorDataSql =
                updateTableSensorSql.arg(sensorId).arg(type);
        qDebug() << "updateTableSensorDataSql: " <<updateTableSensorDataSql;
        if (!query.exec(updateTableSensorDataSql)) {
            qDebug() << "Database table sensor insert failed: " << query.lastError();
        } else {
            qDebug() << "Database table sensor insert sucessful";
        }
    }

    auto updateTableControllerSql =
            QString("INSERT OR REPLACE INTO controller(id, type) VALUES (\"%1\", \"%2\")");

    for (auto controller: controllerArray) {
        auto controllerJsonMap = controller.toObject();
        auto type = controllerJsonMap["type"].toString();
        auto controllerId = controllerJsonMap["controllerId"].toString();
        auto updateTableControllerDataSql =
                updateTableControllerSql.arg(controllerId).arg(type);
        qDebug() << "updateTableControllerSql: " <<updateTableControllerSql;
        if (!query.exec(updateTableControllerSql)) {
            qDebug() << "Database table controller insert failed: " << query.lastError();
        } else {
            qDebug() << "Database table controller insert sucessful";
        }
    }
}

void MosqClientUtils::helperDealWithSensorData(QJsonDocument const& json){
    auto nodeId = json["nodeId"].toString();
    auto sensorArray = json["sensor"].toArray();
    auto controllerArray = json["controller"].toArray();
    auto updateTableSensorSql =
            QString("INSERT OR REPLACE INTO sensor(id, data) VALUES (\"%1\", \"%2\")");

    QSqlQuery query{};
    for (auto sensor: sensorArray) {
        auto sensorJsonMap = sensor.toObject();
        auto data = sensorJsonMap["sensorVal"].toDouble();
        auto sensorId = sensorJsonMap["sensorId"].toString();
        auto updateTableSensorDataSql =
                updateTableSensorSql.arg(sensorId).arg(data);
        qDebug() << "updateTableSensorDataSql: " <<updateTableSensorDataSql;
        if (!query.exec(updateTableSensorDataSql)) {
            qDebug() << "Database table sensor insert failed: " << query.lastError();
        } else {
            qDebug() << "Database table sensor insert sucessful";
        }
    }
}

void MosqClientUtils::helperUpdateRoomId(int roomId) {
    QSqlQuery query{};
    auto updateTableRoomSql =
            QString("INSERT OR REPLACE INTO room(roomId) VALUES (\"%1\")").arg(roomId);
    qDebug() << updateTableRoomSql;
    if (!query.exec(updateTableRoomSql)) {
        qDebug() << "Database table room insert failed: " << query.lastError();
    } else {
        qDebug() << "Database table room insert sucessful";
    }
}

void MosqClientUtils::deleteRoomId(int roomId) {
    QSqlQuery query{};
    auto deleteTableRoomSql =
            QString("DELETE FROM room WHERE roomId = \"%1\"").arg(roomId);
    qDebug() << deleteTableRoomSql;
    if (!query.exec(deleteTableRoomSql)) {
        qDebug() << "Database table room delete failed: " << query.lastError();
    } else {
        qDebug() << "Database table room delete sucessful";
    }
}

QSet<int> MosqClientUtils::selectRoomId() {
    QSet<int> roomIdList;

    auto selectTableRoomSql = QString("SELECT roomId FROM room");
    QSqlQuery query{selectTableRoomSql};
    qDebug() << selectTableRoomSql;

    while (query.next()) {
        auto roomId = query.value(0).toInt();
        roomIdList.insert(roomId);
    }
    return roomIdList;
}

int MosqClientUtils::getNextRoomId() {
    auto numberSet = selectRoomId();
    int index = 1;
    while (numberSet.contains(index)) {
        ++index;
    }
    return index;
}

QSet<QString> MosqClientUtils::selectNodeNotInRoom(int roomId) {
    auto selectTableNodeSql =
            QString{"SELECT id, roomId FROM node WHERE roomId != \"%1\""}.arg(roomId);
    QSqlQuery query{selectTableNodeSql};

    QSet<QString> nodeList;
    while (query.next()) {
        auto nodeId = query.value("id").toString();
        nodeList.insert(nodeId);
    }
    return nodeList;
}

QSet<QString> MosqClientUtils::selectNodeInRoom(int roomId) {
    auto selectTableNodeSql =
            QString{"SELECT id, roomId FROM node WHERE roomId = \"%1\""}.arg(roomId);
    QSqlQuery query{selectTableNodeSql};

    QSet<QString> nodeList;
    while (query.next()) {
        auto nodeId = query.value("id").toString();
        nodeList.insert(nodeId);
    }
    return nodeList;
}
