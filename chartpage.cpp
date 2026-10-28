#include "chartpage.h"
#include "ui_chartpage.h"
#include <QLinearGradient>
#include <QDebug>

ChartPage::ChartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartPage)
{
    ui->setupUi(this);

    chart = new QChart;
    m_line = new QLineSeries;
    m_avg = new QLineSeries;
    area = new QAreaSeries(m_line);

    axisX = new QDateTimeAxis;
    axisY = new QValueAxis;

    m_line->setName("我的");
    QPen greenPen(QColor(76,175,80));
    greenPen.setWidth(2);
    m_line->setPen(greenPen);
    m_line->setPointsVisible(true);
    m_line->setPointLabelsVisible(true);
    m_line->setPointLabelsFormat("@yPoint");
    m_line->setPointLabelsColor(QColor(60, 64, 70));
    QFont labelFont = font();
    labelFont.setPointSize(9);
    m_line->setPointLabelsFont(labelFont);

    m_avg->setName("同车型均值");
    QPen bluePen(QColor(58, 110, 235));
    bluePen.setWidth(2);
    m_avg->setPen(bluePen);

    // =========【关键1】先填充数据，再addSeries！不要先add再clear！=========
    QStringList dates;
    dates << "10-07" << "10-08" << "10-09" << "10-10" << "10-11" << "10-12" << "10-13";
    QVector<double> values;
    values << 5.5 << 4.0 << 3.8 << 4.0 << 4.1 << 4.0 << 4.1;

    m_line->clear();
    m_avg->clear();

    qint64 minTime = 0, maxTime = 0;
    for (int i = 0; i < dates.size(); ++i)
    {
        QDate d = QDate::fromString(dates.at(i), "MM-dd");
        qint64 t = QDateTime(d, QTime(0, 0)).toMSecsSinceEpoch();
        if (i == 0) { minTime = t; maxTime = t; }
        minTime = qMin(minTime, t);
        maxTime = qMax(maxTime, t);
        m_line->append(t, values.at(i));
    }
    m_avg->append(minTime, 5.9);
    m_avg->append(maxTime, 5.9);

    // =========【关键2】给**成员变量axisX**设置范围，不要新建局部变量！=========
    axisX->setMin(QDateTime::fromMSecsSinceEpoch(minTime));
    axisX->setMax(QDateTime::fromMSecsSinceEpoch(maxTime));

    // Y轴设置
    axisY->setRange(0, 10);
    axisY->setTickCount(6);
    axisY->setLabelFormat("%d");
    axisY->setGridLineColor(QColor(235, 238, 242));
    axisY->setLineVisible(false);
    axisY->setLabelsColor(QColor(120, 126, 134));
    labelFont.setPointSize(10);
    axisY->setLabelsFont(labelFont);

    // X轴设置
    axisX->setFormat("MM-dd");
    axisX->setTickCount(7);
    axisX->setGridLineVisible(false);
    axisX->setLineVisible(false);
    axisX->setLabelsColor(QColor(120, 126, 134));
    axisX->setLabelsFont(labelFont);

    // =========【关键3】addSeries顺序：先area面积，再折线，保证折线画在面积上面，不会被遮挡 =========
    QLinearGradient grad(0, 0, 0, 1);
    grad.setCoordinateMode(QGradient::ObjectBoundingMode);
    grad.setColorAt(0.0, QColor(76, 175, 80, 80));
    grad.setColorAt(1.0, QColor(76, 175, 80, 0));
    area->setBrush(grad);
    area->setPen(Qt::NoPen);

    chart->addSeries(area);   // 面积底层先画
    chart->addSeries(m_line); // 折线在上层
    chart->addSeries(m_avg);

    // 添加坐标轴
    chart->addAxis(axisY,Qt::AlignLeft);
    chart->addAxis(axisX,Qt::AlignBottom);

    // series绑定轴
    m_line->attachAxis(axisY);
    m_line->attachAxis(axisX);
    m_avg->attachAxis(axisY);
    m_avg->attachAxis(axisX);
    area->attachAxis(axisY);
    area->attachAxis(axisX);

    chart->legend()->setVisible(true);
    ui->graphicsView->setChart(chart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing); // 开启抗锯齿，线条顺滑
}

ChartPage::~ChartPage()
{
    delete chart; // QChart会自动释放所有series、axis
    delete ui;
}
