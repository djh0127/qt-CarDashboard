#ifndef UDPMANAGER_H
#define UDPMANAGER_H
#include <QString>
#include <QUdpSocket>
#include <QJsonDocument>
class UdpManager: public QObject
{
    Q_OBJECT
    explicit UdpManager(QObject *parent = nullptr);
    UdpManager(const UdpManager&);
    QUdpSocket* socket;
    QString serverIp;
    quint16 serverPort;
public:
    static UdpManager& getUdp();
    void setServerInfo(QString ip,quint16 port);
    void sendUdpJsonData();
};

#endif // UDPMANAGER_H
