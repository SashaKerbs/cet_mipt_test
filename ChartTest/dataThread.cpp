#include <QtCore/QRandomGenerator>

#include "dataThread.h"

DataThread::DataThread() :
    m_pause(false)
{

}

void DataThread::setPause(bool a_pause)
{
    m_pause = a_pause;
}

void DataThread::run()
{
    while(1)
    {
        if(m_pause)
        {
            msleep(c_pauseWaitMs);
            continue;
        }
        qreal xPos = QRandomGenerator::global()->bounded(20);
        qreal yPos = QRandomGenerator::global()->bounded(500);
        QPointF generatePoint(xPos, yPos);

        emit newPoint(generatePoint);
        msleep(c_delayMs);

    }
}
