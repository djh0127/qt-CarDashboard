#include "carconfig.h"

CarConfig CarConfig::instacne;
CarConfig::CarConfig()
{
    setting=new QSettings("config.ini",QSettings::IniFormat);
    if(!setting->contains("/car_status/door_lock"))
    {
        setting->setValue("/car_status/door_lock",0);
    }
    setting_1=new QSettings("config.ini",QSettings::IniFormat);
    if(!setting_1->contains("/car_status1/behind_lock"))
    {
        setting_1->setValue("/car_status1/behind_lock",0);
    }
    if(!setting->contains("/car_air/temperatuer"))
        setting->setValue("/car_air/temperatuer",20);
    if(!setting->contains("/car_air/windon"))
        setting->setValue("/car_air/windon",0); //0关闭，1打开，根据你的业务定义
    if(!setting->contains("/car_air/windmid"))
        setting->setValue("/car_air/windmid",0);
    if(!setting->contains("/car_air/winddown"))
        setting->setValue("/car_air/winddown",0);
    if(!setting->contains("/car_air/level"))
        setting->setValue("/car_air/level",1);
    if(!setting->contains("/car_air/aironoff"))
        setting->setValue("/car_air/aironoff",false);
    if(!setting->contains("/car_air/snow"))
        setting->setValue("/car_air/snow",false);
    if(!setting->contains("/car_air/car"))
        setting->setValue("/car_air/car",false);
    if(!setting->contains("/car_air/auto"))
        setting->setValue("/car_air/auto",false);
    if(!setting->contains("/car_air/front"))
        setting->setValue("/car_air/front",false);
    if(!setting->contains("/car_air/tf"))
            setting->setValue("/car_air/tf",false);
}

CarConfig::CarConfig(const CarConfig &o)
{

}

CarConfig &CarConfig::getConfig()
{
    //    static CarConfig instacne;
    return instacne;
}

void CarConfig::setDoorLock(bool lock)
{
    setting->setValue("/car_status/door_lock",lock?1:0);
}

bool CarConfig::getDoorLock() const
{
    return setting->value("/car_status/door_lock").toBool();
}

void CarConfig::setBehindLock(bool lock)
{
    setting_1->setValue("car_status1/behind_lock",lock?1:0);
}

bool CarConfig::getBehindLock() const
{
    return setting_1->value("car_status1/behind_lock").toBool();
}

int CarConfig::getTemp() const
{
    return setting->value("/car_air/temperatuer").toInt();
}

void CarConfig::setTemp(int temp)
{
    if(temp<16) temp=16;
    if(temp>30) temp=30;
    setting->setValue("/car_air/temperatuer",temp);
    emit sendNewTemperatuer(temp);

}

int CarConfig::getLevel() const
{
    return setting->value("/car_air/level").toInt();
}

void CarConfig::setLevel(int level)
{
    setting->setValue("/car_air/level",level);
}

void CarConfig::setWinOn(bool flag)
{
    setting->setValue("/car_air/windon",flag);
}
bool CarConfig::getWinOn() const
{
    return setting->value("/car_air/windon").toBool();
}

void CarConfig::setWindMid(bool flag)
{
    setting->setValue("/car_air/windmid",flag);
}

bool CarConfig::getWindMid() const
{
    return setting->value("/car_air/windmid").toBool();
}

void CarConfig::setWindDown(bool flag)
{
    setting->setValue("/car_air/winddown",flag);
}

bool CarConfig::getWindDown() const
{
    return setting->value("/car_air/winddown").toBool();
}

void CarConfig::setAuto(bool flag)
{
    setting->setValue("/car_air/auto",flag);
}

bool CarConfig::getAuto() const
{
    return setting->value("/car_air/auto").toBool();
}

void CarConfig::setAironoff(bool flag)
{
    setting->setValue("/car_air/aironoff",flag);
}

bool CarConfig::getAironoff() const
{
    return setting->value("/car_air/aironoff").toBool();
}

void CarConfig::setSnow(bool flag)
{
    setting->setValue("/car_air/snow",flag);
}

bool CarConfig::getSnow() const
{
    return setting->value("/car_air/snow").toBool();
}

void CarConfig::setCar(bool flag)
{
    setting->setValue("/car_air/car",flag);
}

bool CarConfig::getCar() const
{
    return setting->value("/car_air/car").toBool();
}

void CarConfig::setTf(bool flag)
{
    setting->setValue("/car_air/tf",flag);
}

bool CarConfig::getTf() const
{
    return setting->value("/car_air/tf").toBool();
}

void CarConfig::setFront(bool flag)
{
    setting->setValue("/car_air/front",flag);
}

bool CarConfig::getFront() const
{
    return setting->value("/car_air/front").toBool();
}

QJsonObject CarConfig::buildJsonObject()
{
    QJsonObject obj;
    obj["doorLock"] = getDoorLock();
    obj["behindLock"] = getBehindLock();
    obj["temp"] = getTemp();
    obj["level"]=getLevel();
    obj["windon"]=getWinOn();
    obj["windmid"]=getWindMid();
    obj["winddown"]=getWindDown();
    return obj;
}


