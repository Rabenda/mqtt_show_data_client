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
    database = QSqlDatabase::addDatabase("QSQLITE", "data");
    database.setDatabaseName("data.db");
// "create table room(roomId int primary key AUTOINCREMENT)
// "create table node(id char(20) primary key, roomId char(20),status int)"
// "create table controller(id char(20) primary key, type char(20), data float)"
// "create table sensor(id char(20) primary key, type char(20), data float)"

    if (!database.open()) {
        qDebug() << "database open failed: " << database.lastError();
    } else {
        qDebug() << "database open successful";
    }
    QSqlQuery query{database};
    auto tableRoomCreateSql = "CREATE TABLE IF NOT EXISTS room(roomId int primary key)";
    if (!query.exec(tableRoomCreateSql)) {
        qDebug() << "Database table Room create failed: " << query.lastError();
    } else {
        qDebug() << "Database table Room create sucessful";
    }

    auto tableNodeCreateSql = "CREATE TABLE IF NOT EXISTS node(id char(20) primary key, roomId int DEFAULT 0, status int)";
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

    database.close();
}

void MosqClientUtils::helperDealWithOnlineNode(QJsonDocument const& json){
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "helperDealWithOnlineNode");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }
    auto data = json["nodeId"].toString();
    if (data == "")
        return;
    auto updateTableOnlineNodeSql =
            QString("INSERT OR REPLACE INTO node(id, status) VALUES (\"%1\", 1)").arg(data);

    auto requestName = QString("RequestUpdateNode-%1").arg(data);

    auto mosqClient = MosqClient::getInstance();
    mosqClient->send_message(requestName, "None");

    qDebug() << "updateTableOnlineNodeSql : " << updateTableOnlineNodeSql;
    QSqlQuery query{db};
    if (!query.exec(updateTableOnlineNodeSql)) {
        qDebug() << "Database table node insert failed: " << query.lastError();
    } else {
        qDebug() << "Database table node insert sucessful";
    }
    db.close();
}

void MosqClientUtils::helperDealWithUpdateNode(QJsonDocument const& json){
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "helperDealWithUpdateNode");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    auto nodeId = json["nodeId"].toString();
    auto sensorArray = json["sensor"].toArray();
    auto controllerArray = json["controller"].toArray();
    auto updateTableSensorSql =
            QString("INSERT OR REPLACE INTO sensor(id, type) VALUES (\"%1\", \"%2\")");

    QSqlQuery query{db};
    for (auto sensor: sensorArray) {
        auto sensorJsonMap = sensor.toObject();
        auto type = sensorJsonMap["sensorType"].toString();
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
        qDebug() << controllerJsonMap;

        auto type = controllerJsonMap["controllerType"].toString();
        auto controllerId = controllerJsonMap["controllerId"].toString();
        auto updateTableControllerDataSql =
                updateTableControllerSql.arg(controllerId).arg(type);
        qDebug() << "updateTableControllerDataSql: " <<updateTableControllerDataSql;
        if (!query.exec(updateTableControllerDataSql)) {
            qDebug() << "Database table controller insert failed: " << query.lastError();
        } else {
            qDebug() << "Database table controller insert sucessful";
        }
    }

    db.close();
}

void MosqClientUtils::helperDealWithSensorData(QJsonDocument const& json){
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "helperDealWithSensorData");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    auto nodeId = json["nodeId"].toString();
    auto sensorArray = json["sensor"].toArray();
    auto controllerArray = json["controller"].toArray();
    auto updateTableSensorSql =
            QString("UPDATE sensor SET data = %1 WHERE id = \"%2\"");

    QSqlQuery query{db};
    for (auto sensor: sensorArray) {
        auto sensorJsonMap = sensor.toObject();
        auto data = sensorJsonMap["sensorVal"].toDouble();
        auto sensorId = sensorJsonMap["sensorId"].toString();
        auto updateTableSensorDataSql = updateTableSensorSql.arg(data).arg(sensorId);
        qDebug() << "updateTableSensorDataSql: " <<updateTableSensorDataSql;
        if (!query.exec(updateTableSensorDataSql)) {
            qDebug() << "Database table sensor insert failed: " << query.lastError();
        } else {
            qDebug() << "Database table sensor insert sucessful";
        }
    }

    db.close();
}

void MosqClientUtils::helperUpdateRoomId(int roomId) {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "helperUpdateRoomId");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    QSqlQuery query{db};
    auto updateTableRoomSql =
            QString("INSERT OR REPLACE INTO room(roomId) VALUES (\"%1\")").arg(roomId);
    qDebug() << updateTableRoomSql;
    if (!query.exec(updateTableRoomSql)) {
        qDebug() << "Database table room insert failed: " << query.lastError();
    } else {
        qDebug() << "Database table room insert sucessful";
    }

    db.close();
}

void MosqClientUtils::deleteRoomId(int roomId) {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "deleteRoomId");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    QSqlQuery query{db};
    auto deleteTableRoomSql =
            QString("DELETE FROM room WHERE roomId = \"%1\"").arg(roomId);
    qDebug() << deleteTableRoomSql;
    if (!query.exec(deleteTableRoomSql)) {
        qDebug() << "Database table room delete failed: " << query.lastError();
    } else {
        qDebug() << "Database table room delete sucessful";
    }

    db.close();
}

QSet<int> MosqClientUtils::selectRoomId() {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "selectRoomId");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    QSet<int> roomIdList;

    auto selectTableRoomSql = QString("SELECT roomId FROM room");
    QSqlQuery query{selectTableRoomSql, db};
    qDebug() << selectTableRoomSql;

    while (query.next()) {
        auto roomId = query.value(0).toInt();
        roomIdList.insert(roomId);
    }
    db.close();

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
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "selectNodeNotInRoom");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    auto selectTableNodeSql =
            QString{"SELECT id, roomId FROM node WHERE roomId != %1"}.arg(roomId);
    QSqlQuery query{selectTableNodeSql, db};

    QSet<QString> nodeList;
    while (query.next()) {
        auto nodeId = query.value("id").toString();
        nodeList.insert(nodeId);
    }

    db.close();

    return nodeList;
}

QSet<QString> MosqClientUtils::selectNodeInRoom(int roomId) {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "selectNodeInRoom");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    auto selectTableNodeSql =
            QString{"SELECT id, roomId FROM node WHERE roomId = %1;"}.arg(roomId);
    QSqlQuery query{selectTableNodeSql, db};

    QSet<QString> nodeList;
    while (query.next()) {
        auto nodeId = query.value("id").toString();
        nodeList.insert(nodeId);
    }

    db.close();

    return nodeList;
}

void MosqClientUtils::updateNodeRoomId(int roomId, QStringList const& list) {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "updateNodeRoomId");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }

    auto updateNodeRoomIdSql =
            QString{"INSERT OR REPLACE INTO node(id, roomId) VALUES (\"%1\", \"%2\")"};

    QSqlQuery query{db};
    for (auto const& nodeId: list) {
        auto sql = updateNodeRoomIdSql.arg(nodeId).arg(roomId);
        qDebug() << sql;
        if (!query.exec(sql)) {
            qDebug() << "Database table node update failed: " << query.lastError();
        } else {
            qDebug() << "Database table node update sucessful";
        }
    }
    db.close();
}

QVector<Sensor> MosqClientUtils::selectSensorFromRoomId(int roomId) {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "selectSensorFromRoomId");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }
    auto nodeList = selectNodeInRoom(roomId);
    QSqlQuery query{db};
    QVector<Sensor> sensorList;
    auto selectSensorDataSql =
            QString{"SELECT id, type, data FROM sensor WHERE id like \"%1*\""};
    for (auto const& nodeId: nodeList) {
        auto sql = selectSensorDataSql.arg(nodeId);
        qDebug() << sql;
        if (!query.exec(sql)) {
            qDebug() << "Database table node update failed: " << query.lastError();
        } else {
            qDebug() << "Database table node update sucessful";
        }
        while (query.next()) {
            Sensor sensor;
            sensor.id = query.value("id").toString();
            sensor.type = query.value("type").toString();
            sensor.data = query.value("data").toDouble();
            sensorList.append(sensor);
        }
    }
    db.close();

    return sensorList;
}

QVector<Controller> MosqClientUtils::selectControllerFromRoomId(int roomId) {
    QSqlDatabase db = QSqlDatabase::cloneDatabase(database, "selectControllerFromRoomId");
    if (!db.open()) {
        qDebug() << "database open failed: " << db.lastError();
    } else {
        qDebug() << "database open successful";
    }
    auto nodeList = selectNodeInRoom(roomId);
    QSqlQuery query{db};
    QVector<Controller> controllerList;
    auto selectControllerDataSql =
            QString{"SELECT id, type, data FROM controller WHERE id like \"%1*\""};
    for (auto const& nodeId: nodeList) {
        auto sql = selectControllerDataSql.arg(nodeId);
        qDebug() << sql;
        if (!query.exec(sql)) {
            qDebug() << "Database table node update failed: " << query.lastError();
        } else {
            qDebug() << "Database table node update sucessful";
        }
        while (query.next()) {
            Controller controller;
            controller.id = query.value("id").toString();
            controller.type = query.value("type").toString();
            controller.data = query.value("data").toDouble();
            controllerList.append(controller);
        }
    }
    db.close();

    return controllerList;
}

