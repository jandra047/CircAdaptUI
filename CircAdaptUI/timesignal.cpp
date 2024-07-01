#include "timesignal.h"
#include "settings.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void TimeSignal::updateGraph(Buffer& buffer)
{
    // Get all the data from the buffer
    QVector<double> yData = buffer.get(m_yVar, 1/(double)Settings::instance().fps());
    QVector<double> tData = buffer.get(m_xVar, 1/(double)Settings::instance().fps());

    // Shift time data to start from current m_xPos
    double tOffset = m_xPos - tData[0];
    double dt = tData[1] - tData[0];
    for (int i = 0; i < tData.size(); ++i) {
        tData[i] += tOffset + dt;
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
        data()->remove(0, fmod(x1, keyAxis()->range().upper));
        data()->remove(x0, keyAxis()->range().upper);
        addData(keyAxis()->range().upper, quiet_nan);
    }
    else
    {
        data()->remove(x0, x1);
        addData(x1, quiet_nan);
    }
}
