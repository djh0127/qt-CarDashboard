#include "mainwindow.h"

#include <QApplication>
#include "udpmanager.h"
int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    UdpManager::getUdp().setServerInfo("127.0.0.1",12345);
    UdpManager::getUdp().sendUdpJsonData();
    MainWindow w;
    w.show();
    return a.exec();
}
