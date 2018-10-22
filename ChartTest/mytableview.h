#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H
#include <QTableView>

class MyTableView : public QTableView
{
public:
    MyTableView(QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYTABLEVIEW_H
