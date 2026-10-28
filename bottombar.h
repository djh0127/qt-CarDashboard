#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>

namespace Ui {
class BottomBar;
}

class BottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = nullptr);
    ~BottomBar();

private:
    Ui::BottomBar *ui;
};

#endif // BOTTOMBAR_H
