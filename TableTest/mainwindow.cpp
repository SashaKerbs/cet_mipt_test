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
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model->setParent(ui->tableView);
    connect(ui->insertRowButton, SIGNAL(clicked()), this, SLOT(onInsertRow()));
    connect(ui->removeRowButton, SIGNAL(clicked()), this, SLOT(onRemoveRow()));

// fill table
    addRowInModel(1, 1, 1);
    addRowInModel(2, 2, 2);
    addRowInModel(5, -1, 20);
    addRowInModel(5.5, 0, 9.9);
    addRowInModel(10, 2, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInsertRow()
{
    QModelIndex index = ui->tableView->currentIndex();
    QAbstractItemModel *model = ui->tableView->model();
    model->insertRows(index.isValid() ? index.row() : 0, 1);
}

void MainWindow::onRemoveRow()
{
    QModelIndex index = ui->tableView->currentIndex();
    QAbstractItemModel *model = ui->tableView->model();
    model->removeRows(index.isValid() ? index.row() : 0, 1);
}

void MainWindow::addRowInModel(qreal x, qreal y, qreal z)
{
    int rowNewPoint = 0;
    onInsertRow();
    QAbstractItemModel *model = ui->tableView->model();
    QModelIndex indexX = model->index(rowNewPoint, PointTableModel::X);
    model->setData(indexX, x);
    QModelIndex indexY = model->index(rowNewPoint, PointTableModel::Y);
    model->setData(indexY, y);
    QModelIndex indexZ = model->index(rowNewPoint, PointTableModel::Z);
    model->setData(indexZ, z);
}
