#include "airscreen.h"
#include "ui_airscreen.h"
#include "carconfig.h"
#include <QDebug>
AirScreen::AirScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);

    connect(&CarConfig::getConfig(), &CarConfig::sendNewTemperatuer, this, [=](){
        int temp=CarConfig::getConfig().getTemp();
        if(temp==16)
        {
            ui->label_2->setNum(CarConfig::getConfig().getTemp());
            ui->label->setNum((CarConfig::getConfig().getTemp())+1);
            ui->label_3->setText("");
        }
        else if(temp==30)
        {
            ui->label->setText("");
            ui->label_2->setNum(CarConfig::getConfig().getTemp());
            ui->label_3->setNum((CarConfig::getConfig().getTemp())-1);
        }
        else
        {
            ui->label_2->setNum(CarConfig::getConfig().getTemp());
            ui->label->setNum((CarConfig::getConfig().getTemp())+1);
            ui->label_3->setNum((CarConfig::getConfig().getTemp())-1);
        }
    });
    int temp=CarConfig::getConfig().getTemp();
    if(temp==16)
    {
        ui->label_2->setNum(CarConfig::getConfig().getTemp());
        ui->label->setNum((CarConfig::getConfig().getTemp())+1);
        ui->label_3->setText("");
    }
    else if(temp==30)
    {
        ui->label->setText("");
        ui->label_2->setNum(CarConfig::getConfig().getTemp());
        ui->label_3->setNum((CarConfig::getConfig().getTemp())-1);
    }
    else
    {
        ui->label_2->setNum(CarConfig::getConfig().getTemp());
        ui->label->setNum((CarConfig::getConfig().getTemp())+1);
        ui->label_3->setNum((CarConfig::getConfig().getTemp())-1);
    }
    int level=CarConfig::getConfig().getLevel();
    ui->widget->setLevel(level);
    updateWindUI();
    updateTopBtnUI();
}

AirScreen::~AirScreen()
{
    delete ui;
}

void AirScreen::on_pushButton_clicked()
{
    int temp=CarConfig::getConfig().getTemp();
    temp++;
    CarConfig::getConfig().setTemp(temp);

}

void AirScreen::on_pushButton_2_clicked()
{
    int temp=CarConfig::getConfig().getTemp();
    temp--;
    CarConfig::getConfig().setTemp(temp);

}


void AirScreen::on_pushButton_windon_clicked()
{
    bool status=CarConfig::getConfig().getWinOn();
    status=!status;
    CarConfig::getConfig().setWinOn(status);
    updateWindUI(); //只调用这个函数刷新界面
}

void AirScreen::on_pushButton_windmid_clicked()
{
    bool status=CarConfig::getConfig().getWindMid();
    status=!status;
    CarConfig::getConfig().setWindMid(status);
    updateWindUI();
}

void AirScreen::on_pushButton_winddown_clicked()
{
    bool status=CarConfig::getConfig().getWindDown();
    status=!status;
    CarConfig::getConfig().setWindDown(status);
    updateWindUI();
}

void AirScreen::on_pushButton_auto_clicked()
{
    bool status = CarConfig::getConfig().getAuto();
    status = !status;
    CarConfig::getConfig().setAuto(status);
    updateTopBtnUI();
}

void AirScreen::on_pushButton_aironoff_clicked()
{
    bool status = CarConfig::getConfig().getAironoff();
    status = !status;
    CarConfig::getConfig().setAironoff(status);
    updateTopBtnUI();
}

void AirScreen::on_pushButton_snow_clicked()
{
    bool status = CarConfig::getConfig().getSnow();
    status = !status;
    CarConfig::getConfig().setSnow(status);
    updateTopBtnUI();
}

void AirScreen::on_pushButton_car_clicked()
{
    bool status = CarConfig::getConfig().getCar();
    status = !status;
    CarConfig::getConfig().setCar(status);
    updateTopBtnUI();
}

void AirScreen::on_pushButton_tf_clicked()
{
    bool status = CarConfig::getConfig().getTf();
        status = !status;
        CarConfig::getConfig().setTf(status);
        updateTopBtnUI();
}

void AirScreen::on_pushButton_front_clicked()
{
    bool status = CarConfig::getConfig().getFront();
    status = !status;
    CarConfig::getConfig().setFront(status);
    updateTopBtnUI();
}

void AirScreen::updateWindUI()
{
    qDebug()<<CarConfig::getConfig().getWinOn();
    if(CarConfig::getConfig().getWinOn())
    {
        QPixmap pix(":/background/background/air/up_open.png");
        ui->label_windon->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/background/background/air/up_no.png");
        ui->label_windon->setPixmap(pix);
    }
    ui->label_windon->setScaledContents(true);

    //中窗
    if(CarConfig::getConfig().getWindMid())
    {
        QPixmap pix(":/background/background/air/mid_open.png");
        ui->label_mid->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/background/background/air/mid_no.png");
        ui->label_mid->setPixmap(pix);
    }
    ui->label_mid->setScaledContents(true);

    //下窗
    if(CarConfig::getConfig().getWindDown())
    {
        QPixmap pix(":/background/background/air/down_open.png");
        ui->label_windown->setPixmap(pix);
    }
    else
    {
        QPixmap pix(":/background/background/air/down_no.png");
        ui->label_windown->setPixmap(pix);
    }
    ui->label_windown->setScaledContents(true);
}

void AirScreen::updateTopBtnUI()
{
    // pushButton_aironoff 空调开关
        if(CarConfig::getConfig().getAironoff())
        {
            ui->pushButton_aironoff->setIcon(QIcon(":/background/background/air/wind_btn_open.png"));
        }
        else
        {
            QString picPath = ":/background/background/air/wind_btn_lock.png"; //false关闭图片，自行填写
            ui->pushButton_aironoff->setIcon(QIcon(picPath));
        }

        // pushButton_snow 雪花制冷
        if(CarConfig::getConfig().getSnow())
        {
            QString picPath = ":/background/background/air/snow_icon_select.png";
            ui->pushButton_snow->setIcon(QIcon(picPath));
        }
        else
        {
            QString picPath = ":/background/background/air/snow_icon.png";
            ui->pushButton_snow->setIcon(QIcon(picPath));
        }

        // pushButton_car 内循环小车
        if(CarConfig::getConfig().getCar())
        {
            QString picPath = ":/background/background/air/loop_open.png";
            ui->pushButton_car->setIcon(QIcon(picPath));
        }
        else
        {
            QString picPath = ":/background/background/air/loop_lock.png";
            ui->pushButton_car->setIcon(QIcon(picPath));
        }

        // pushButton_auto 自动
        if(CarConfig::getConfig().getAuto())
        {
            QString picPath = ":/background/background/air/auto_icon_select.png";
            ui->pushButton_auto->setIcon(QIcon(picPath));
        }
        else
        {
            QString picPath = ":/background/background/air/auto_icon.png";
            ui->pushButton_auto->setIcon(QIcon(picPath));
        }

        // ============新增 通风 pushButton_tf============
        if(CarConfig::getConfig().getTf())
        {
            QString picPath = ":/background/background/air/windding_select.png"; //开启图片路径，自己填
            ui->pushButton_tf->setIcon(QIcon(picPath));
        }
        else
        {
            QString picPath = ":/background/background/air/windding.png"; //关闭图片路径，自己填
            ui->pushButton_tf->setIcon(QIcon(picPath));
        }

        // pushButton_front 前除雾
        if(CarConfig::getConfig().getFront())
        {
            QString picPath = ":/background/background/air/wram_seelct.png";
            ui->pushButton_front->setIcon(QIcon(picPath));
        }
        else
        {
            QString picPath = ":/background/background/air/wram.png";
            ui->pushButton_front->setIcon(QIcon(picPath));
        }
}
