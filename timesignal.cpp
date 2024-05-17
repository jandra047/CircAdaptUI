#include "timesignal.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void TimeSignal::updateGraph()
{
    removeData(m_xPos, m_xPos + m_dt);
    addData(m_xPos, m_y[i]);
    i %= m_t.size() - 1;
    m_xPos += m_t[1] - m_t[0];
    m_xPos = fmod(m_xPos, keyAxis()->range().upper);
    i += 1;
    // data()->remove(m_xPos, m_xPos + m_dt);
    addData(m_xPos + m_dt, quiet_nan);
}
// void TimeSignal::updateGraph2(Buffer& buffer)
// {
//     QVector<double> yData = buffer.take(m_name, 0.025);
//     QVector<double> tData = buffer.take("t", 0.025);

//     // Shift time data to start from current m_xPos
//     for (int i = 0; i < tData.size(); ++i) {
//         tData[i] += m_xPos;
//     }

//     // Remove old data before plotting the new segment
//     removeData(m_xPos, tData.last() + m_dt);

//     // Plot the new segment
//     addData(tData, yData);

//     // Update m_xPos for the next segment
//     m_xPos = fmod(tData.last(), keyAxis()->range().upper);
// }

void TimeSignal::updateGraph2(Buffer& buffer)
{
    // Get all the data from the buffer
    QVector<double> yData = buffer.take(m_name, 0.015);
    QVector<double> tData = buffer.get("t", 0.015);

    // Shift time data to start from current m_xPos
    double tOffset = m_xPos - tData[0];
    double dt = tData[1] - tData[0];
    for (int i = 0; i < tData.size(); ++i) {
        tData[i] += tOffset + dt;
    }

    // Remove old data before plotting the new data
    removeData(m_xPos, tData.last() + m_dt);

    // Plot the new data
    addData(tData, yData);

    // Update m_xPos for the next segment
    m_xPos = fmod(tData.last(), keyAxis()->range().upper);
}

// void TimeSignal::updateGraph2(Buffer& buffer)
// {
//     QVector<double> out = buffer.take(m_name, 0.01);
//     QVector<double> t = buffer.take("t", 0.01);
//     for (auto& t : t)
//     {
//         t += m_xPos;
//     }
//     removeData(m_xPos, m_xPos + m_dt);
//     addData(t, out);
//     m_xPos += t.last();
//     m_xPos = fmod(m_xPos, keyAxis()->range().upper);
//     // data()->remove(m_xPos, m_xPos + m_dt);
//     removeData(m_xPos, m_xPos + m_dt);
//     addData(t, out);
//     addData(m_xPos + m_dt, quiet_nan);
// }

void TimeSignal::removeData(double const x0, double x1)
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
