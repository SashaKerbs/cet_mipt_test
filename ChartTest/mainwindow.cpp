
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QBarSet>
#include <QtCharts/QVBarModelMapper>
#include <QtWidgets/QHeaderView>
#include <QtCharts/QBarCategoryAxis>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //m_model = new PointListModel(this);
    ui->setupUi(this);
    addChart();
    addButton();

    m_dataThread = new DataThread();
    connect(m_dataThread, SIGNAL(newPoint(QPointF)), this, SLOT(onNewPoint(QPointF)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_dataThread;
}

void MainWindow::onNewPoint(QPointF point)
{
    m_series->append(point.x(), point.y());
}

void MainWindow::onPlay()
{
    m_dataThread->setPause(false);
    if (!m_dataThread->isRunning())
        m_dataThread->start();
}

void MainWindow::onPause()
{
    m_dataThread->setPause(true);
}

void MainWindow::onStop()
{
    m_dataThread->terminate();
    m_series->clear();
}

void MainWindow::addChart()
{
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);

    m_series = new QScatterSeries;
    chart->addSeries(m_series);

    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 20);
    chart->axisY()->setRange(0, 500);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    ui->verticalLayout->addWidget(chartView, 1);
}

void MainWindow::addButton()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout(this);

    QPushButton *playButton = new QPushButton(tr("Play"), this);
    buttonLayout->addWidget(playButton);
    connect(playButton, SIGNAL(clicked()), this, SLOT(onPlay()));

    QPushButton * pauseButton = new QPushButton(tr("Pause"), this);
    buttonLayout->addWidget(pauseButton);
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(onPause()));

    QPushButton * stopButton = new QPushButton(tr("Stop"), this);
    buttonLayout->addWidget(stopButton);
    connect(stopButton, SIGNAL(clicked()), this, SLOT(onStop()));

    ui->verticalLayout->addLayout(buttonLayout);
}
