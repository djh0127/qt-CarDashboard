#ifndef SYSTEM_H
#define SYSTEM_H
#include <QSettings>

class System
{
private:
    System();
    System(const System&other);
    System operator=(const System&other);
    static System system;
    QSettings* set;
public:
    static System& getconfig()
    {
        return system;
    }

    void setCurrentIndex(int index);
    int getCurrentIndex() const;
    void saveName(QString name);
    QString getName()const;
};

#endif // SYSTEM_H
