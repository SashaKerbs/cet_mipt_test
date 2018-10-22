#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QScatterSeries>

#include "dataThread.h"
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onNewPoint(QPointF point);
    void onPlay();
    void onPause();
    void onStop();
private:
    void addChart();
    void addButton();
private:
    Ui::MainWindow *ui;
    QScatterSeries *m_series;
    DataThread *m_dataThread;
};

#endif // MAINWINDOW_H
