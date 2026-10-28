#ifndef CARCONFIG_H
#define CARCONFIG_H
#include <QObject>
#include<QSettings>
#include <QJsonObject>
class CarConfig:public QObject
{
    Q_OBJECT
    CarConfig();
    CarConfig(const CarConfig& o);
    QSettings* setting;
    QSettings* setting_1;
    static CarConfig instacne;
signals:
    void sendNewTemperatuer(int temp);
public:
    static CarConfig& getConfig();
    void setDoorLock(bool lock);
    bool getDoorLock()const;
    void setBehindLock(bool lock);
    bool getBehindLock()const;
    int getTemp()const;
    void setTemp(int temp);
    int getLevel()const;
    void setLevel(int level);
    void setWinOn(bool flag);
    bool getWinOn()const;
    void setWindMid(bool flag);
    bool getWindMid()const;
    void setWindDown(bool flag);
    bool getWindDown()const;
    void setAuto(bool flag);
    bool getAuto()const;
    void setAironoff(bool flag);
    bool getAironoff()const;
    void setSnow(bool flag);
    bool getSnow()const;
    void setCar(bool flag);
    bool getCar()const;
    void setTf(bool flag);
    bool getTf()const;
    void setFront(bool flag);
    bool getFront()const;
    QJsonObject buildJsonObject();
};

#endif // CARCONFIG_H
