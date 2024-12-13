#include "timesignal.h"
#include <QPixmap>
#include <QPainter>

void TimeSignal::updateGraph(Buffer& buffer, double timeInterval)
{
    timeInt = timeInterval;
    // Get all the data from the buffer
    buffer.lock();
    QVector<double> yData = buffer.get(m_yVar, timeInterval);
    QVector<double> tData = buffer.get(m_xVar, timeInterval);
    buffer.unlock();

    if (!newLines.isEmpty())
        newLines.erase(newLines.cbegin(), newLines.cend() - 1);
    // Shift time data to start from current m_xPos
    double dt = tData[1] - tData[0];
    for (int i = 0; i < tData.size(); ++i) {
        tData[i] = m_xPos + i*dt;
        try
        {
            newLines.push_back({
                                keyAxis()->coordToPixel(tData[i]),
                                valueAxis()->coordToPixel(yData[i])});
        }
        catch( const std::exception& e)
        {
            qDebug() << "Couldn't add";
        }
    }

    // Remove old data before plotting the new data
    removeData(m_xPos, tData.last() + m_dt);

    // Plot the new data
    addData(tData, yData, true);

    // Update m_xPos for the next segment
    m_xPos = fmod(tData.last(), keyAxis()->range().upper);

}

void TimeSignal::removeData(double const x0, double const x1)
{
    if (x1 > keyAxis()->range().upper)
    {
        data()->removeBefore(fmod(x1, keyAxis()->range().upper));
        data()->removeAfter(x0);
        addData(keyAxis()->range().upper, qQNaN());
    }
    else
    {
        data()->remove(x0, x1);
        addData(x1, qQNaN());
    }
}

void TimeSignal::drawLinePlot(QCPPainter* painter, const QVector<QPointF> &lines) const
{
    if (parentPlot()->currentLayer()->mode() == QCPLayer::lmRealtime && !newLines.isEmpty())
    {
        QCPGraph::drawLinePlot(painter, newLines);
    }
    else
    {
        QCPGraph::drawLinePlot(painter, lines);
    }
}

void TimeSignal::reset()
{
    data()->clear();
    m_xPos = 0;
}

