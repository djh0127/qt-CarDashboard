#include "themescreen.h"
#include "ui_themescreen.h"

ThemeScreen::ThemeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    for(int i=1;i<=9;i++)
    {
        QString path=QString(":/background/background/bg/bg%1.png").arg(i);
        imgpaths.push_back(path);
    }
    for(int i=0;i<imgpaths.size();i++)
    {
        QLabel* item=new QLabel(this);
        item->setPixmap(QPixmap(imgpaths.at(i)));
        item->setScaledContents(true);
        item->setFixedSize(QSize(120,100));
        ui->gridLayout->addWidget(item,i/3,i%3);
        list_lables.push_back(item);
        item->installEventFilter(this);
        item->setObjectName(QString::number(i));
    }
}

ThemeScreen::~ThemeScreen()
{
    delete ui;
}

bool ThemeScreen::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        QLabel* label=dynamic_cast<QLabel*>(watched);
        if(label==nullptr)
        {
            return false;
        }
        for(auto item:list_lables)
        {
            item->setStyleSheet("border:2px solid transparent;border-radius:6px;");
        }
        label->setStyleSheet("border:3px solid #1E90FF; border-radius:6px;");
        QString index=label->objectName();
        imgIndex=index.toInt();
        return true;
    }
    return QWidget::eventFilter(watched,event);
}



void ThemeScreen::on_pushButton_clicked()
{
    QString path=imgpaths.at(imgIndex);
    changeBackground(path);
    emit changeBackground(path);
}
