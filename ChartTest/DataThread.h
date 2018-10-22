#ifndef DATATREAD_H
#define DATATREAD_H

#include <QThread>
#include <QPointF>

class DataThread : public QThread
{
    Q_OBJECT

public:
    DataThread();
    void setPause(bool a_pause);
    void run() override;

signals:
    void newPoint(QPointF a_point);

private:
    const uint c_delayMs = 500;
    const uint c_pauseWaitMs = 200;
    bool m_pause;
    //PointListModel *m_model;

};

#endif // DATATREAD_H
