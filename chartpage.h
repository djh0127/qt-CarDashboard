#ifndef CHARTPAGE_H
#define CHARTPAGE_H
#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QDateTime>
#include <QAreaSeries>
#include <QtCharts/QChartView>   // ✅新增

QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class ChartPage;
}
QT_END_NAMESPACE

class ChartPage : public QWidget
{
    Q_OBJECT
public:
    explicit ChartPage(QWidget *parent = nullptr);
    ~ChartPage();

private:
    Ui::ChartPage *ui;
    QLineSeries* m_line;
    QLineSeries* m_avg;
    QAreaSeries* area;

    QChart* chart;
    QDateTimeAxis* axisX;
    QValueAxis* axisY;
};
#endif // CHARTPAGE_H
