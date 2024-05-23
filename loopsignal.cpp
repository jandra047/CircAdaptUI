#include "loopsignal.h"
#include "settings.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void LoopSignal::updateGraph(Buffer& buffer)
{
    // TODO: Implement loop graph drawing logic

    QVector<double> yData = buffer.get(m_yVar, 1000/((double)Settings::instance().fps() * 1000));
    QVector<double> xData = buffer.get(m_xVar, 1000/((double)Settings::instance().fps() * 1000));
    QVector<double> tData = buffer.get("t", 1000/((double)Settings::instance().fps() * 1000));


    data()->remove(tData.last(), tData.last() + m_dt);

    addData(tData, xData, yData);
    addData(tData.last() + m_dt, tData.last() + m_dt, quiet_nan);

}

void LoopSignal::removeData(double const x0, double x1)
{
    if (x1 > keyAxis()->range().upper)
    {
        x1 = fmod(x1, keyAxis()->range().upper);
        data()->remove(0, x1);
        data()->remove(x0, keyAxis()->range().upper);
    }
    else
    {
        data()->remove(x0, x1);
    }
    addData(x1, quiet_nan);
}
