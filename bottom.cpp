#include "bottom.h"
#include "ui_bottom.h"
#include "carconfig.h"
#include "airscreen.h"
Bottom::Bottom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bottom)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    connect(ui->pushButton_home,&QPushButton::clicked,this,&Bottom::changePageHome);
    connect(ui->pushButton_air,&QPushButton::clicked,this,&Bottom::changePageAir);
    connect(ui->pushButton_phone,&QPushButton::clicked,this,&Bottom::changePagePhone);
    connect(ui->pushButton_theme,&QPushButton::clicked,this,&Bottom::changePageTheme);
    connect(&CarConfig::getConfig(), &CarConfig::sendNewTemperatuer, this, [=]()
    {
        ui->label->setNum(CarConfig::getConfig().getTemp());
    });
    ui->label->setNum(CarConfig::getConfig().getTemp());
}

Bottom::~Bottom()
{
    delete ui;
}



void Bottom::on_pushButton_3_clicked()
{
    int temp=CarConfig::getConfig().getTemp();
    temp--;
    CarConfig::getConfig().setTemp(temp);
    ui->label->setNum(CarConfig::getConfig().getTemp());

}

void Bottom::on_pushButton_4_clicked()
{
    int temp=CarConfig::getConfig().getTemp();
    temp++;
    CarConfig::getConfig().setTemp(temp);
    ui->label->setNum(CarConfig::getConfig().getTemp());

}

//void Bottom::dealNewTemperatuer()
//{
//    ui->label->setNum(CarConfig::getConfig().getTemp());
//}
