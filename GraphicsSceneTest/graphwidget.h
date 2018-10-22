#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QVector>
#include <QModelIndex>
#include "pointItem.h"
#include "lineItem.h"
#include "pointTableModel.h"

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    void setModel(PointTableModel *a_model);
    void pointPosChanged(PointItem *point, QPointF a_pos);

private slots:
    void addPoints(const QModelIndex & parent, int first, int last);
    void removePoints(const QModelIndex & parent, int first, int last);
    void onPointsPosChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &);

private:
    void addPoint(int pointN);
    void removePoint(int pointN);

private:
    QVector <PointItem *> points;
    QVector <LineItem *> lines;
    PointTableModel *model;
};

#endif // GRAPHWIDGET_H
