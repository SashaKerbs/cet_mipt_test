#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pointTableModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PointTableModel *model = new PointTableModel(this);
    ui->tableView->setModel(model);
    ui->graphicsView->setModel(model);
    connect(ui->insertRowButton, SIGNAL(clicked()), this, SLOT(onInsertRow()));
    connect(ui->removeRowButton, SIGNAL(clicked()), this, SLOT(onRemoveRow()));

    // fill table
    addRowInModel(-176.25, 148.75);
    addRowInModel(-119.75, 71.25);
    addRowInModel(-3, -10);
    addRowInModel(136.25, -3.75);
    addRowInModel(212.5, -146.25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInsertRow()
{
    QModelIndex index = ui->tableView->currentIndex();
    QAbstractItemModel *model = ui->tableView->model();
    model->insertRows(index.isValid() ? index.row() + 1 : 0, 1);
}

void MainWindow::onRemoveRow()
{
    QModelIndex index = ui->tableView->currentIndex();
    QAbstractItemModel *model = ui->tableView->model();
    model->removeRows(index.isValid() ? index.row() : 0, 1);
}

void MainWindow::addRowInModel(qreal x, qreal y)
{
    int rowNewPoint = 0;
    onInsertRow();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex indexX = model->index(rowNewPoint, PointTableModel::X);
    model->setData(indexX, x);
    QModelIndex indexY = model->index(rowNewPoint, PointTableModel::Y);
    model->setData(indexY, y);
}

