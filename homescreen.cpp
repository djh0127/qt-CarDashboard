#include "homescreen.h"
#include "ui_homescreen.h"
#include <QDateTime>
#include <QMediaMetaData>
#include "carconfig.h"
HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    time=new QTimer(this);
    connect(time,&QTimer::timeout,this,&HomeScreen::changeTimelable);
    time->start(1000);
    player=new QMediaPlayer(this);
    paths.push_back("C:/Users/Lenovo/Downloads/music/music/萧敬腾 - 王妃.mp3");
    paths.push_back("C:/Users/Lenovo/Downloads/music/music/Flo Rida - Whistle.mp3");
    paths.push_back("C:/Users/Lenovo/Downloads/music/music/Eric周兴哲 - 你，好不好？.mp3");
    paths.push_back("C:/Users/Lenovo/Downloads/music/music/Eric周兴哲 - 永不失联的爱.mp3");
    paths.push_back("C:/Users/Lenovo/Downloads/music/music/薛之谦 - 动物世界.mp3");
    player->setMedia(QUrl::fromLocalFile(paths.at(count)));
    connect(player,&QMediaPlayer::mediaStatusChanged,this,&HomeScreen::on_mediaStatusChanged);
    if(!CarConfig::getConfig().getDoorLock())
    {
        ui->pushButton_doorlock->setIcon(QIcon(":/background/background/main/suo.png"));
    }
    else
    {
        ui->pushButton_doorlock->setIcon(QIcon(":/background/background/main/unlock.png"));

    }
    if(!CarConfig::getConfig().getBehindLock())
    {
        ui->pushButton_behindlock->setIcon(QIcon(":/background/background/main/box_lock.png"));
    }
    else
    {
        ui->pushButton_behindlock->setIcon(QIcon(":/background/background/main/box_open.png"));

    }
    label=new MyLabel(this);
    connect(ui->pushButton_fule,&QPushButton::clicked,this,&HomeScreen::tochartpage);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::changeTimelable()
{
    QDateTime datetime=QDateTime::currentDateTime();
    QString t=datetime.toString("HH:mm");
    QString date=datetime.toString("MM/dd ddd");
    ui->label->setText(t+'\n'+date);
}

void HomeScreen::on_pushButton_prev_clicked()
{
    bool wasPlaying = (player->state() == QMediaPlayer::PlayingState);
    count--;
    if(count<0)
        count=paths.size()-1;
    player->setMedia(QUrl::fromLocalFile(paths.at(count)));
    if(wasPlaying)
        {
            player->play();
        }
        else
        {
            player->pause();
        }
}

void HomeScreen::on_pushButton_on_clicked()
{
    if(player->state()==QMediaPlayer::PlayingState)
    {
        player->pause();
        ui->pushButton_on->setIcon(QIcon("C:/Users/Lenovo/Downloads/background/background/main/play.png"));
    }
    else if(player->state()==QMediaPlayer::PausedState||player->state()==QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_on->setIcon(QIcon("C:/Users/Lenovo/Downloads/background/background/main/pause.png"));
    }
    getMusicInfo();
}

void HomeScreen::on_pushButton_next_clicked()
{
    bool wasPlaying = (player->state() == QMediaPlayer::PlayingState);
    count++;
    if(count>=paths.size())
        count=0;
    player->setMedia(QUrl::fromLocalFile(paths.at(count)));
    if(wasPlaying)
        {
            player->play();
        }
        else
        {
            player->pause();
        }
}

void HomeScreen::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status==QMediaPlayer::LoadedMedia||status==QMediaPlayer::BufferedMedia)
        getMusicInfo();
}

void HomeScreen::getMusicInfo()
{
    QVariant title = player->metaData(QMediaMetaData::Title);//标题
    ui->label_title->setText(title.toString());

    // 先试封面，再试缩略图
    QVariant v = player->metaData(QMediaMetaData::CoverArtImage);//封面
    if (!v.isValid())
    {
        v = player->metaData(QMediaMetaData::ThumbnailImage);//缩略图
    }
    if (v.canConvert<QImage>())
    {
        QImage img = v.value<QImage>();
        if (!img.isNull())
        {
            ui->label_picture->setPixmap(QPixmap::fromImage(img).scaled(
                ui->label_picture->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void HomeScreen::on_pushButton_doorlock_clicked()
{
    bool status=CarConfig::getConfig().getDoorLock();
    status=!status;
    CarConfig::getConfig().setDoorLock(status);
    if(status)
    {
        ui->pushButton_doorlock->setIcon(QIcon(":/background/background/main/unlock.png"));
        label->toastLabel("四门已打开");
    }
    else
    {
        ui->pushButton_doorlock->setIcon(QIcon(":/background/background/main/suo.png"));
        label->toastLabel("四门已关闭");
    }
    }

void HomeScreen::on_pushButton_behindlock_clicked()
{
    bool status=CarConfig::getConfig().getBehindLock();
    status=!status;
    CarConfig::getConfig().setBehindLock(status);
    if(status)
    {
        ui->pushButton_behindlock->setIcon(QIcon(":/background/background/main/box_open.png"));
        label->toastLabel("后备箱已打开");

    }else
    {
        ui->pushButton_behindlock->setIcon(QIcon(":/background/background/main/box_lock.png"));
        label->toastLabel("后备箱已关闭");
    }
}

void HomeScreen::on_pushButton_car_clicked()
{

}
