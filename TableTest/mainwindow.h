#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MyTableView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onInsertRow();
    void onRemoveRow();

private:
    void addRowInModel(qreal x, qreal y, qreal z);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
