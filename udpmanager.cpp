#include "udpmanager.h"
#include "carconfig.h"
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>

UdpManager::UdpManager(QObject *parent)
    : QObject(parent) // 初始化父类QObject
{
    socket = new QUdpSocket(this);
}
UdpManager::UdpManager(const UdpManager &)
{

}

UdpManager &UdpManager::getUdp()
{
    static UdpManager instance;
    return instance;
}

void UdpManager::setServerInfo(QString ip, quint16 port)
{
    this->serverIp=ip;
    this->serverPort=port;
}

void UdpManager::sendUdpJsonData()
{
    QJsonObject obj=CarConfig::getConfig().buildJsonObject();
    QJsonDocument doc(obj);
    QByteArray arr=doc.toJson(QJsonDocument::Compact);
    socket->writeDatagram(arr,QHostAddress(serverIp),serverPort);
    qDebug()<<"udp发送给服务器的json字符串"<<arr;
}
