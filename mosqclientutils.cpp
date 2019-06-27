#include "mosqclientutils.hpp"
#include <QDebug>
MosqClientUtils* MosqClientUtils::instance = nullptr;

QMutex MosqClientUtils::mutex;

MosqClientUtils* MosqClientUtils::getInstance() {
    QMutexLocker locker(&mutex);
    if (instance == nullptr)
        instance = new MosqClientUtils;
    return instance;
}

MosqClientUtils::MosqClientUtils(QObject *parent) : QObject(parent)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.db");

    if (!database.open()) {
        qDebug() << "database open failed: " << database.lastError();
    } else {
        qDebug() << "database open successful";
    }
// "create table node(id char(20) primary key, roomId int, status int)"
// "create table controller(id char(20) primary key, type char(20), data float)"
// "create table sensor(id char(20) primary key, type char(20), data float)"
    QSqlQuery query;
    auto tableNodeCreateSql = "CREATE TABLE IF NOT EXISTS node(id char(20) primary key, roomId int, status int)";
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

}

void MosqClientUtils::helperDealWithUpdateNode(QJsonDocument const& json){

}

void MosqClientUtils::helperDealWithSensorData(QJsonDocument const& json){

}
