#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system.h"
#include "phonescreen.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    phone=new PhoneScreen(this);
    ui->stackedWidget->addWidget(phone);
    connect(ui->bot,&Bottom::changePagePhone,this,&MainWindow::dealPagePhone);
    connect(ui->bot,&Bottom::changePageHome,this,&MainWindow::dealPageHome);

    connect(ui->bot,&Bottom::changePageAir,this,&MainWindow::dealPageAir);
    connect(ui->bot,&Bottom::changePageTheme,this,&MainWindow::dealPageTheme);
    connect(ui->home,&HomeScreen::changePageTheme,this,&MainWindow::dealPageTheme);
    connect(ui->theme,&ThemeScreen::changeBackground,this,&MainWindow::dealchangeBackground);
    connect(ui->home,&HomeScreen::tochartpage,this,[this]()
    {
        ui->stackedWidget->setCurrentIndex(3);
    });
    int index=System::getconfig().getCurrentIndex();
    ui->stackedWidget->setCurrentIndex(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dealPageHome()
{
    ui->stackedWidget->setCurrentIndex(0);
    System::getconfig().setCurrentIndex(0);
}

void MainWindow::dealPageAir()
{
    ui->stackedWidget->setCurrentIndex(2);
    System::getconfig().setCurrentIndex(2);
}

void MainWindow::dealPageTheme()
{
    ui->stackedWidget->setCurrentIndex(1);
    System::getconfig().setCurrentIndex(1);
}

void MainWindow::dealPagePhone()
{
    ui->stackedWidget->setCurrentWidget(phone);
    System::getconfig().setCurrentIndex(ui->stackedWidget->currentIndex());
}

void MainWindow::dealchangeBackground(QString imgpath)
{
    QString styleSheet = QString("HomeScreen{border-image:url(%1);}").arg(imgpath);
    ui->home->setStyleSheet(styleSheet);
    qDebug()<<imgpath;
    ui->stackedWidget->setCurrentIndex(0);
    System::getconfig().setCurrentIndex(0);
}
