#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent):QLabel(parent)
{
    setStyleSheet(R"(
                  QLabel{
                  color: white;
                  font-size: 16px;
                  background-color: rgba(51,51,51,0.7);
                  border-radius: 8px;
                  padding: 10px 20px;
                  }
                  )");
    hide();
    timer=new QTimer(this);
    timer->setSingleShot(true);
    connect(timer,&QTimer::timeout,this,&QLabel::hide);
}
void MyLabel::toastLabel(QString str)
{
    setText(str);
    this->adjustSize();
    raise();
    show();
    move(450,300);
    timer->start(1000);
}
