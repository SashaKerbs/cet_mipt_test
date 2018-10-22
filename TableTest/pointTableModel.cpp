#include "pointTableModel.h"
#include <QVariant>

PointTableModel::PointTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

PointTableModel::~PointTableModel()
{
    m_data.clear();
}

int PointTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

int PointTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return AxisCount;
}

Qt::ItemFlags PointTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsDragEnabled | Qt::ItemIsEditable | QAbstractItemModel::flags(index);

}

QVariant PointTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case X:
                return QString("X");
            case Y:
                return QString("Y");
            case Z:
                return QString("Z");
            }
        }

        if (orientation == Qt::Vertical) {
            return QString::number(section);
        }
    }

    return QVariant();
}

QVariant PointTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case X:
            return m_data[index.row()].x;
        case Y:
            return m_data[index.row()].y;
        case Z:
            return m_data[index.row()].z;
        }
    }
    return QVariant();
}

bool PointTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        bool isConverted;
        qreal val = value.toReal(&isConverted);
        Position &pos = m_data[index.row()];
        if (isConverted) {
            switch (index.column())
            {
            case X:
                pos.x = val;
                break;
            case Y:
                pos.y = val;
                break;
            case Z:
                pos.z = val;
                break;
            }
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

bool PointTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    if (count < 1 || row < 0 || row > rowCount())
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);
    m_data.insert(row, count, Position());
    endInsertRows();
    return true;

}


bool PointTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    int  rowC = rowCount();
    if (count < 1 || row < 0 || (row + count) > rowC)
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();
    return true;
}


