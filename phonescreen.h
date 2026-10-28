#ifndef PHONESCREEN_H
#define PHONESCREEN_H

#include <QWidget>
#include <QSqlDatabase>   // 数据库连接对象（值类型，需要完整定义）

// 前向声明：只用到指针的类，可以只声明不包含头文件，减少编译依赖
class QLabel;
class QStackedWidget;
class QListWidget;
class QListWidgetItem;

class PhoneScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PhoneScreen(QWidget *parent = nullptr);
    ~PhoneScreen();

private slots:
    void switchToContacts();                      // 从拨号页切到通讯录页
    void switchToDial();                          // 从通讯录页切回拨号页
    void addContact();                            // 弹窗输入姓名电话并存入数据库
    void onContactClicked(QListWidgetItem *item); // 点击通讯录里的联系人

private:
    void setupDialPage();      // 构建拨号子页面（数字键盘 + 号码显示label）
    void setupContactsPage();  // 构建通讯录子页面（联系人列表 + 添加按钮）
    void initDatabase();       // 打开SQLite数据库并创建contacts表
    void loadContacts();       // 查询数据库所有联系人，刷新列表显示

    QWidget *dialPage;         // 拨号子页
    QWidget *contactsPage;     // 通讯录子页
    QStackedWidget *stack;     // 两个子页的容器，实现拨号/通讯录来回切换
    QLabel *labelNumber;       // 拨号页顶部显示号码的label
    QListWidget *listContacts; // 通讯录页的联系人列表
    QSqlDatabase db;           // 数据库连接（SQLite）
};

#endif // PHONESCREEN_H
