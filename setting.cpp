#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
}

Setting::~Setting()
{
    delete ui;
}
