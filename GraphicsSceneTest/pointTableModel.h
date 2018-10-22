#ifndef POINTLISTMODEL_H
#define POINTLISTMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QList>
#include <QtCore/QPointF>

class PointTableModel : public QAbstractTableModel
{
public:
    enum Axis{
        X = 0,
        Y = 1,
        ErrorAxis,
        AxisCount = ErrorAxis,
        LastAxis = ErrorAxis - 1
    };

public:

    PointTableModel(QObject *parent = nullptr);
    virtual ~PointTableModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    struct Position {
        Position() : x(0), y(0) {}
        qreal x;
        qreal y;
    };

    QVector<Position> m_data;
};

#endif // POINTLISTMODEL_H
