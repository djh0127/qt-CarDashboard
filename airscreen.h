#ifndef AIRSCREEN_H
#define AIRSCREEN_H

#include <QWidget>

namespace Ui {
class AirScreen;
}

class AirScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AirScreen(QWidget *parent = nullptr);
    ~AirScreen();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
//    void dealTemperatuer();
    void on_pushButton_windon_clicked();

    void on_pushButton_windmid_clicked();

    void on_pushButton_winddown_clicked();

    void on_pushButton_auto_clicked();

    void on_pushButton_aironoff_clicked();

    void on_pushButton_snow_clicked();

    void on_pushButton_car_clicked();

    void on_pushButton_tf_clicked();

    void on_pushButton_front_clicked();

private:
    Ui::AirScreen *ui;
    void updateWindUI();
    void updateTopBtnUI();
};

#endif // AIRSCREEN_H
