#ifndef BOTTOM_H
#define BOTTOM_H

#include <QWidget>

namespace Ui {
class Bottom;
}

class Bottom : public QWidget
{
    Q_OBJECT

public:
    explicit Bottom(QWidget *parent = nullptr);
    ~Bottom();
signals:
    void changePageHome();
    void changePageAir();
    void changePageTheme();
    void changePagePhone();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
//    void dealNewTemperatuer();

private:
    Ui::Bottom *ui;
};

#endif // BOTTOM_H
