#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QTimer>

class MyLabel : public QLabel
{
public:
    MyLabel(QWidget* parent=nullptr);
    void toastLabel(QString str);
private:
    QTimer* timer;
};

#endif // MYLABEL_H
