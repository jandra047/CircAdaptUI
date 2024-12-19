#include "timesignal.h"
#include <QPixmap>
#include <QPainter>

void TimeSignal::updateGraph(Buffer& buffer, double timeInterval)
{
    // Get all the data from the buffer
    QVector<double> yData = buffer.get(m_yVar, timeInterval);
    QVector<double> tData = buffer.get(m_xVar, timeInterval);

    // Leave last point for smoother transition
    if (!newLines.isEmpty())
        newLines.erase(newLines.cbegin(), newLines.cend() - 1);

    // Shift time data to start from current m_xPos
    double dt = 0.002; // TODO: Should come from the ModelWrapper
    for (int i = 0; i < tData.size(); ++i)
    {
        static double pos = 0;
        pos = m_xPos + (i+1)*dt;
        tData[i] = pos;
        try
        {
            if (pos >= keyAxis()->range().upper)
                newLines.push_back({qQNaN(), qQNaN()});

            newLines.push_back({
                                keyAxis()->coordToPixel(fmod(pos, keyAxis()->range().upper)),
                                valueAxis()->coordToPixel(yData[i])});
        }
        catch( const std::exception& e)
        {
            qDebug() << "Couldn't add";
        }
    }

    // Remove old data before plotting the new data
    removeData(m_xPos, m_xPos+(tData.size()*dt) + m_dt);

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

