#include "system.h"

System System::system;
System::System()
{
    set=new QSettings("config.ini",QSettings::IniFormat);
}

System::System(const System &other)
{

}

System System::operator=(const System &other)
{

}

int System::getCurrentIndex() const
{
    int index=set->value("project/index").toInt();
    return index;
}

void System::saveName(QString name)
{
    set->setValue("project/name",name);
}

QString System::getName() const
{
    return set->value("project/name").toString();
}

void System::setCurrentIndex(int index)
{
    set->setValue("/project/index",index);
}

