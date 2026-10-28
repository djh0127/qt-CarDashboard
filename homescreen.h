#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>
#include <QList>
#include "mylabel.h"
namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

signals:
    void changePageTheme();
    void tochartpage();
private slots:
    void changeTimelable();
    void on_pushButton_prev_clicked();

    void on_pushButton_on_clicked();

    void on_pushButton_next_clicked();
    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_pushButton_doorlock_clicked();

    void on_pushButton_behindlock_clicked();

    void on_pushButton_car_clicked();

private:
    void getMusicInfo();
    Ui::HomeScreen *ui;
    QTimer* time;
    QMediaPlayer* player;
    QList<QString> paths;
    int count=0;
    MyLabel* label;
};

#endif // HOMESCREEN_H
