#include "loopsignal.h"
#include "settings.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void LoopSignal::updateGraph(Buffer& buffer)
{

    QVector<double> yData = buffer.get(m_yVar, 1000/((double)Settings::instance().fps() * 1000));
    QVector<double> xData = buffer.get(m_xVar, 1000/((double)Settings::instance().fps() * 1000));
    QVector<double> tData = buffer.get("t", 1000/((double)Settings::instance().fps() * 1000));


    addData(tData, xData, yData);
    if (!data()->isEmpty())
    {
        removeData(tData.last(), tData.last() + m_dt);
    }

}

void LoopSignal::removeData(double const x0, double const x1)
{
    double last = data()->constEnd()->sortKey();
    if (x1 > last)
    {
        data()->remove(0, fmod(x1, last));
        data()->remove(x0, last);
    }
    else
    {
        data()->remove(x0, x1);
    }
    addData(x1, x1, quiet_nan);

void LoopSignal::displaySnapshot(const Buffer& buffer)
{
    QVector<double> yData = buffer.getSnapshot(m_yVar);
    QVector<double> tData = buffer.getSnapshot(m_xVar);
}
