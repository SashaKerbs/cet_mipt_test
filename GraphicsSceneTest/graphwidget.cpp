
#include "graphwidget.h"
#include "lineItem.h"
#include "pointItem.h"
#include "pointTableModel.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QGraphicsScene>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
}

void GraphWidget::setModel(PointTableModel *a_model)
{
    model = a_model;
    connect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
            this, SLOT(addPoints(const QModelIndex &, int, int)));
    connect(model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
            this, SLOT(removePoints(const QModelIndex &, int, int)));

    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(onPointsPosChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));
}

void GraphWidget::pointPosChanged(PointItem *point, QPointF a_pos)
{
    disconnect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
               this, SLOT(onPointsPosChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

    int pointNum = points.indexOf(point);
    model->setData(model->index(pointNum, PointTableModel::X), a_pos.x());
    model->setData(model->index(pointNum, PointTableModel::Y), a_pos.y());

    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(onPointsPosChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));
}

void GraphWidget::addPoints(const QModelIndex & parent , int first , int last)
{
    Q_UNUSED(parent)
    for (int i = first; i <= last; ++i) {
        addPoint(i);
    }
}

void GraphWidget::removePoints(const QModelIndex & parent, int first, int last)
{
    Q_UNUSED(parent)
    for (int i = last; i >= first; --i) {
        removePoint(i);
    }
}

void GraphWidget::onPointsPosChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &)
{
    for(int row = topLeft.row(); row <= bottomRight.row(); ++row) {
        QModelIndex indexX = model->index(row, PointTableModel::X);
        qreal x = model->data(indexX).toReal();
        QModelIndex indexY = model->index(row, PointTableModel::Y);
        qreal y = model->data(indexY).toReal();
        points[row]->setPos(x, y);
    }
}

void GraphWidget::addPoint(int pointN)
{
    if (pointN < 0 || pointN > points.size())
        return;

    PointItem *pointItem = new PointItem(this);

    if (!points.empty()) {
        if (pointN == 0) {
            PointItem *nextPoint = points[pointN];
            LineItem *nextLine = new LineItem(pointItem, nextPoint);
            lines.insert(0, nextLine);
            scene()->addItem(nextLine);

        } else if (pointN == points.size()) {
            PointItem *prewPoint = points[pointN - 1];
            LineItem *prewLine = new LineItem(prewPoint, pointItem);
            lines.insert(pointN - 1, prewLine);
            scene()->addItem(prewLine);

        } else {
            PointItem *prewPoint = points[pointN - 1];
            LineItem *prewLine = new LineItem(prewPoint, pointItem);

            PointItem *nextPoint = points[pointN];
            LineItem *nextLine = new LineItem(pointItem, nextPoint);

            scene()->removeItem(lines[pointN - 1]);
            delete lines[pointN - 1];

            lines[pointN - 1] = prewLine;
            lines.insert(pointN, nextLine);
            scene()->addItem(prewLine);
            scene()->addItem(nextLine);
        }
    }
    points.insert(pointN, pointItem);
    scene()->addItem(pointItem);
}

void GraphWidget::removePoint(int pointN)
{
    if (!lines.empty()) {
        if (pointN == 0) {
            scene()->removeItem(lines[0]);
            delete lines[0];
            lines.remove(0);
        } else if (pointN == points.size() - 1) {
            scene()->removeItem(lines[pointN - 1]);
            delete lines[pointN - 1];
            lines.remove(pointN - 1);
        } else {
            scene()->removeItem(lines[pointN]);
            delete lines[pointN];
            lines.remove(pointN);
            scene()->removeItem(lines[pointN - 1]);
            delete lines[pointN - 1];
            lines.remove(pointN - 1);
            PointItem *prewPoint = points[pointN - 1];
            PointItem *nextPoint = points[pointN + 1];
            LineItem *newLine = new LineItem(prewPoint, nextPoint);
            lines.insert(pointN - 1, newLine);
            scene()->addItem(newLine);
        }
    }
    PointItem *deleteItem = points[pointN];
    scene()->removeItem(deleteItem);
    points.removeAt(pointN);
    delete deleteItem;
}

