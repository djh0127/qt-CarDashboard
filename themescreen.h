#ifndef THEMESCREEN_H
#define THEMESCREEN_H

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QEvent>
namespace Ui {
class ThemeScreen;
}

class ThemeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeScreen(QWidget *parent = nullptr);
    ~ThemeScreen();
    bool eventFilter(QObject* watched,QEvent* event);
signals:
    void changeBackground(QString imgpath);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ThemeScreen *ui;
    QList<QString> imgpaths;
    QList<QLabel*> list_lables;
    int imgIndex=0;
};

#endif // THEMESCREEN_H
