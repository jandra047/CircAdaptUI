#include "loopsignal.h"
#include "CircAdaptUI/loopmarker.h"
#include "CircAdaptUI/settings.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void LoopSignal::updateGraph(Buffer& buffer, double timeInterval)
{

    buffer.lock();
    QVector<double> yData = buffer.get(m_yVar, timeInterval);
    QVector<double> xData = buffer.get(m_xVar, timeInterval);
    QVector<double> tData = buffer.get("t", timeInterval);
    buffer.unlock();

    addData(tData, xData, yData);
    if (Settings::instance().beatIdx() > 0)
    {
        if (!data()->isEmpty())
        {
            removeData(tData.last(), tData.last() + m_dt, buffer);
        }
    }
}

void LoopSignal::removeData(double const x0, double const x1, Buffer& buffer)
{
    // double last = data()->constEnd()->sortKey();
    double last = buffer.getLastBeat()->get("t").last();
    if (x1 > last)
    {
        data()->remove(0, fmod(x1, last));
        data()->removeAfter(x0);
    }
    else
    {
        data()->remove(x0, x1);
    }
    addData(x1, quiet_nan, quiet_nan);
}
void LoopSignal::setVisible(bool isVisible)
{

    if (m_marker)
    {
        m_marker->setVisible(isVisible);
    }
    QCPCurve::setVisible(isVisible);
};

void LoopSignal::createMarker()
{
    m_marker = new LoopMarker(this);
    m_marker->setLayer("markers");
}

void LoopSignal::clear()
{
    data()->clear();
    if (m_marker)
        m_marker->setVisible(false);
}

void LoopSignal::reset()
{
    clear();
}
