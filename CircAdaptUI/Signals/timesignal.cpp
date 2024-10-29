#include "timesignal.h"
#include "CircAdaptUI/settings.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void TimeSignal::updateGraph(Buffer& buffer, double timeInterval)
{
    // Get all the data from the buffer
    buffer.lock();
    QVector<double> yData = buffer.get(m_yVar, timeInterval);
    QVector<double> tData = buffer.get(m_xVar, timeInterval);
    buffer.unlock();

    // Shift time data to start from current m_xPos
    double dt = tData[1] - tData[0];
    for (int i = 0; i < tData.size(); ++i) {
        tData[i] = m_xPos + i*dt;
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
        addData(keyAxis()->range().upper, quiet_nan);
    }
    else
    {
        data()->remove(x0, x1);
        addData(x1, quiet_nan);
    }
}
