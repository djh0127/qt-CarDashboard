#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class PhoneScreen;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void dealPageHome();
    void dealPageAir();
    void dealPageTheme();
    void dealPagePhone();
    void dealchangeBackground(QString imgpath);
private:
    Ui::MainWindow *ui;
    PhoneScreen *phone;
};
#endif // MAINWINDOW_H
