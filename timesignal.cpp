#include "timesignal.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void TimeSignal::updateGraph()
{
    addData(m_xPos, m_xPos, m_y[i]);
    i %= m_t.size() - 1;
    m_xPos += m_t[1] - m_t[0];
    m_xPos = fmod(m_xPos, keyAxis()->range().upper);
    i += 1;
    removeData(m_xPos, m_xPos + m_dt);
    // data()->remove(m_xPos, m_xPos + m_dt);
    addData(m_xPos + m_dt, m_xPos + m_dt, quiet_nan);
}

void TimeSignal::removeData(double const x0, double x1)
{
    if (x1 > keyAxis()->range().upper)
    {
        x1 = fmod(x1, keyAxis()->range().upper);

        for (int i = 0; i < data()->size(); i++)
        {
            auto const dp = data()->at(i);
            if (dp->mainKey() >= x0 || dp->mainKey() <= x1)
            {
                data()->remove(dp->sortKey());
            }

        }
    }
    else
    {
        for (int i = 0; i < data()->size(); i++)
        {
            auto const dp = data()->at(i);
            if (dp->mainKey() >= x0 && dp->mainKey() <= x1)
            {
                data()->remove(dp->sortKey());
            }

        }
    }
}
