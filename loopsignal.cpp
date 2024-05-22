#include "loopsignal.h"
#include "settings.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void LoopSignal::updateGraph(Buffer& buffer)
{
    // TODO: Implement loop graph drawing logic

    // Get all the data from the buffer
    QVector<double> tData = buffer.get("t", 1000/((double)Settings::instance().fps() * 1000));
    QVector<double> yData = buffer.get(m_name, 1000/((double)Settings::instance().fps() * 1000));

    // Shift time data to start from current m_xPos
    // double tOffset = m_xPos - tData[0];
    // double dt = tData[1] - tData[0];
    // for (int i = 0; i < tData.size(); ++i) {
    //     tData[i] += tOffset + dt;
    // }

    // Remove old data before plotting the new data
    // removeData(m_xPos, tData.last() + m_dt);

    // Plot the new data
    // addData(tData, yData);

    // Update m_xPos for the next segment
    // m_xPos = fmod(tData.last(), keyAxis()->range().upper);
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
