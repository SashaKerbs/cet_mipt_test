#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include "myTableView.h"

MyTableView::MyTableView(QWidget *parent) :
    QTableView(parent)
{

}

void MyTableView::keyPressEvent(QKeyEvent *event)
{
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        if(event->key() == Qt::Key_Insert)
            model()->insertRows(selectedRows.at(0).row(),
                                selectedRows.size());
        else if(event->key() == Qt::Key_Delete)
            model()->removeRows(selectedRows.at(0).row(),
                                selectedRows.size());
    }
    if (!selectedIndexes().isEmpty()) {
        if (event->key() == Qt::Key_Delete && selectedRows.isEmpty()) {
            foreach (QModelIndex index, selectedIndexes())
                model()->setData(index, 0);
        } else if (event->matches(QKeySequence::Copy)) {
            QString text;
            QItemSelectionRange range = selectionModel()->selection().first();
            for (auto i = range.top(); i <= range.bottom(); ++i) {
                QStringList rowContents;
                for (auto j = range.left(); j <= range.right(); ++j)
                    rowContents << model()->index(i,j).data().toString();
                text += rowContents.join("\t");
                text += "\n";
            }
            QApplication::clipboard()->setText(text);
        }
        else if (event->matches(QKeySequence::Paste)) {
            QString text = QApplication::clipboard()->text();
            QStringList rowContents = text.split("\n", QString::SkipEmptyParts);

            QModelIndex initIndex = selectedIndexes().at(0);
            selectionModel()->select(initIndex, QItemSelectionModel::Deselect);
            auto initRow = initIndex.row();
            auto initCol = initIndex.column();
            for (auto i = 0; i < rowContents.size(); ++i) {
                QStringList columnContents = rowContents.at(i).split("\t");
                int sizeCol = columnContents.size();
                for (auto j = 0; j < sizeCol; ++j) {
                    QModelIndex index = model()->index(initRow + i, initCol + j);
                    if (index.isValid()) {
                        model()->setData(index, columnContents.at(j));
                        selectionModel()->select(index, QItemSelectionModel::Select);
                    }
                }
            }
        }
    }
    QTableView::keyPressEvent(event);
}
