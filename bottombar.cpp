#include "bottombar.h"
#include "ui_bottombar.h"

BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);
}

BottomBar::~BottomBar()
{
    delete ui;
}
