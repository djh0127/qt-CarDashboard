#include "phonescreen.h"
#include <QStackedWidget>    // 堆栈容器
#include <QLabel>            // 号码显示
#include <QPushButton>       // 按键
#include <QGridLayout>       // 数字键盘网格布局
#include <QVBoxLayout>       // 垂直布局
#include <QHBoxLayout>       // 水平布局
#include <QListWidget>       // 联系人列表
#include <QListWidgetItem>   // 列表条目
#include <QInputDialog>      // 输入弹窗（添加联系人用）
#include <QSqlQuery>         // SQL查询
#include <QSqlError>         // 数据库错误信息
#include <QMessageBox>       // 错误提示弹窗
#include <QDebug>

PhoneScreen::PhoneScreen(QWidget *parent)
    : QWidget(parent)
{
    // 让这个Widget可以接受QSS背景
    setAttribute(Qt::WA_StyledBackground);
    // 背景沿用项目现有的深色背景图
    setStyleSheet("PhoneScreen{background-image: url(:/background/background/bg/set4.png);}");

    // 1. 分别构建拨号页和通讯录页
    setupDialPage();
    setupContactsPage();

    // 2. 用QStackedWidget把两个子页装起来（同时只显示一个）
    stack = new QStackedWidget(this);
    stack->addWidget(dialPage);     // 索引0：拨号页（默认显示）
    stack->addWidget(contactsPage); // 索引1：通讯录页

    // 3. 堆栈填满整个PhoneScreen
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // 去掉边距，铺满
    layout->addWidget(stack);

    // 4. 打开数据库，加载已有联系人
    initDatabase();
    loadContacts();
}

PhoneScreen::~PhoneScreen()
{
    // 关闭数据库连接
    if (db.isOpen())
        db.close();
}

// ==================== 拨号子页 ====================
void PhoneScreen::setupDialPage()
{
    dialPage = new QWidget(this);

    // 顶部号码显示label：大字号、白字、半透明圆角背景
    labelNumber = new QLabel("", dialPage);
    labelNumber->setAlignment(Qt::AlignCenter);
    labelNumber->setMinimumHeight(80);
    labelNumber->setStyleSheet(
        "QLabel{color:white; font-size:48px; font-weight:bold;"
        " background-color:rgba(255,255,255,0.1); border-radius:10px;}");

    // 电话键盘的12个字符，按手机键盘顺序排列
    QStringList keys;
    keys << "1" << "2" << "3"
         << "4" << "5" << "6"
         << "7" << "8" << "9"
         << "*" << "0" << "#";

    // 按键统一样式：白字、半透明圆角；按下时变亮（:pressed）
    QString btnStyle =
        "QPushButton{color:white; font-size:28px;"
        " background-color:rgba(255,255,255,0.15); border-radius:25px;}"
        "QPushButton:pressed{background-color:rgba(255,255,255,0.35);}";

    // 3列网格：i/3是行，i%3是列，正好排成 4行×3列
    QGridLayout *grid = new QGridLayout;
    grid->setSpacing(12);
    for (int i = 0; i < keys.size(); ++i)
    {
        QPushButton *btn = new QPushButton(keys.at(i), dialPage);
        btn->setFixedSize(70, 70);
        btn->setStyleSheet(btnStyle);
        btn->setCursor(Qt::PointingHandCursor); // 鼠标悬停显示手型
        // 点击任意按键：把该按钮上的字符追加到顶部label后面
        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            labelNumber->setText(labelNumber->text() + btn->text());
        });
        grid->addWidget(btn, i / 3, i % 3);
    }

    // 删除按钮：去掉号码最后一个字符（用户没要求，但拨错号时很实用，可选）
    QPushButton *btnClear = new QPushButton("删除", dialPage);
    btnClear->setStyleSheet(
        "QPushButton{color:white; font-size:20px;"
        " background-color:rgba(255,80,80,0.8); border-radius:20px; min-height:50px;}");
    connect(btnClear, &QPushButton::clicked, this, [this]() {
        QString text = labelNumber->text();
        if (!text.isEmpty())
            labelNumber->setText(text.left(text.size() - 1)); // 去掉最后一位
    });

    // 通讯录按钮：切到通讯录页
    QPushButton *btnContacts = new QPushButton("通讯录", dialPage);
    btnContacts->setStyleSheet(
        "QPushButton{color:white; font-size:20px;"
        " background-color:rgba(30,144,255,0.8); border-radius:20px; min-height:50px;}");
    connect(btnContacts, &QPushButton::clicked, this, &PhoneScreen::switchToContacts);

    // 底部一排：左边删除，右边通讯录
    QHBoxLayout *bottomRow = new QHBoxLayout;
    bottomRow->addWidget(btnClear);
    bottomRow->addWidget(btnContacts);

    // 拨号页整体布局：号码label → 数字键盘 → 底部按钮排
    QVBoxLayout *mainLayout = new QVBoxLayout(dialPage);
    mainLayout->addWidget(labelNumber);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(grid, 1); // 键盘占据剩余主要空间
    mainLayout->addLayout(bottomRow);
}

// ==================== 通讯录子页 ====================
void PhoneScreen::setupContactsPage()
{
    contactsPage = new QWidget(this);

    // 页面标题
    QLabel *title = new QLabel("通讯录", contactsPage);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel{color:white; font-size:28px; font-weight:bold;}");

    // 联系人列表：半透明圆角背景，条目之间有分隔线，悬停高亮
    listContacts = new QListWidget(contactsPage);
    listContacts->setStyleSheet(
        "QListWidget{background-color:rgba(255,255,255,0.1);"
        " border-radius:10px; color:white; font-size:20px;}"
        "QListWidget::item{padding:12px; border-bottom:1px solid rgba(255,255,255,0.15);}"
        "QListWidget::item:hover{background-color:rgba(30,144,255,0.3);}");
    // 单击联系人条目即触发
    connect(listContacts, &QListWidget::itemClicked,
            this, &PhoneScreen::onContactClicked);

    // 添加联系人按钮
    QPushButton *btnAdd = new QPushButton("添加联系人", contactsPage);
    btnAdd->setStyleSheet(
        "QPushButton{color:white; font-size:20px;"
        " background-color:rgba(30,144,255,0.8); border-radius:20px; min-height:50px;}");
    connect(btnAdd, &QPushButton::clicked, this, &PhoneScreen::addContact);

    // 返回拨号按钮
    QPushButton *btnBack = new QPushButton("返回拨号", contactsPage);
    btnBack->setStyleSheet(
        "QPushButton{color:white; font-size:20px;"
        " background-color:rgba(120,120,120,0.8); border-radius:20px; min-height:50px;}");
    connect(btnBack, &QPushButton::clicked, this, &PhoneScreen::switchToDial);

    // 底部一排：左边添加，右边返回
    QHBoxLayout *btnRow = new QHBoxLayout;
    btnRow->addWidget(btnAdd);
    btnRow->addWidget(btnBack);

    // 通讯录页整体布局
    QVBoxLayout *layout = new QVBoxLayout(contactsPage);
    layout->addWidget(title);
    layout->addWidget(listContacts, 1); // 列表占主要空间
    layout->addLayout(btnRow);
}

// ==================== 数据库 ====================
void PhoneScreen::initDatabase()
{
    // 使用独立连接名"contactConn"，避免和程序其他数据库连接冲突
    db = QSqlDatabase::addDatabase("QSQLITE", "contactConn");
    // 数据库文件 contacts.db 会创建在程序运行目录下（和config.ini同级）
    db.setDatabaseName("contacts.db");

    if (!db.open())
    {
        QMessageBox::warning(this, "错误", "打开数据库失败：" + db.lastError().text());
        return;
    }

    // 建表：如果表不存在才创建
    QSqlQuery query(db);
    bool ok = query.exec("CREATE TABLE IF NOT EXISTS contacts("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT," // 自增主键
                         "name TEXT NOT NULL,"                    // 联系人姓名
                         "phone TEXT NOT NULL)");                 // 电话号码
    if (!ok)
        QMessageBox::warning(this, "错误", "建表失败：" + query.lastError().text());
}

void PhoneScreen::loadContacts()
{
    // 清空列表，重新从数据库读取（添加联系人后调用它来刷新）
    listContacts->clear();

    QSqlQuery query(db);
    query.exec("SELECT name, phone FROM contacts ORDER BY id"); // 按添加顺序显示
    while (query.next())
    {
        QString name = query.value(0).toString();  // 第0列：name
        QString phone = query.value(1).toString(); // 第1列：phone

        // 列表里显示"姓名   电话"，方便一眼看到是谁
        QListWidgetItem *item = new QListWidgetItem(name + "    " + phone, listContacts);
        // 把电话号码存到条目的UserRole自定义数据里，点击时取出来
        item->setData(Qt::UserRole, phone);
    }
}

// ==================== 槽函数 ====================
void PhoneScreen::addContact()
{
    // 第一次弹窗：输入姓名（取消或为空则直接返回，不添加）
    bool okName = false;
    QString name = QInputDialog::getText(this, "添加联系人", "请输入姓名：",
                                         QLineEdit::Normal, "", &okName);
    if (!okName || name.isEmpty())
        return;

    // 第二次弹窗：输入电话号码
    bool okPhone = false;
    QString phone = QInputDialog::getText(this, "添加联系人", "请输入电话号码：",
                                          QLineEdit::Normal, "", &okPhone);
    if (!okPhone || phone.isEmpty())
        return;

    // 用参数绑定方式插入数据库（防止SQL注入）
    QSqlQuery query(db);
    query.prepare("INSERT INTO contacts(name, phone) VALUES(?, ?)");
    query.addBindValue(name);
    query.addBindValue(phone);
    if (!query.exec())
    {
        QMessageBox::warning(this, "错误", "添加失败：" + query.lastError().text());
        return;
    }

    // 添加成功后刷新列表，让新联系人立刻显示出来
    loadContacts();
}

void PhoneScreen::onContactClicked(QListWidgetItem *item)
{
    // 取出该联系人存在UserRole里的电话号码
    QString phone = item->data(Qt::UserRole).toString();
    // 把号码显示到拨号页顶部的label
    labelNumber->setText(phone);
    // 自动跳回拨号页
    switchToDial();
}

void PhoneScreen::switchToContacts()
{
    stack->setCurrentWidget(contactsPage); // 显示通讯录页
}

void PhoneScreen::switchToDial()
{
    stack->setCurrentWidget(dialPage);     // 显示拨号页
}
