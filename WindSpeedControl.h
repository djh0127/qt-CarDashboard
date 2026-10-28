#ifndef WINDSPEEDCONTROL_H
#define WINDSPEEDCONTROL_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class WindSpeedControl : public QWidget
{
    Q_OBJECT
public:
    explicit WindSpeedControl(QWidget *parent = nullptr);

    int getLevel() const { return m_level; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_level = 3;    // 当前档位
    int m_maxLevel = 7; // 共7档

signals:
    void levelChanged(int level);

public slots:
    void setLevel(int lvl , bool sendUdp = true);
};

#endif // WINDSPEEDCONTROL_H
