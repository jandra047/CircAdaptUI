#include "signal.h"

void Signal::updateGraph()
{
    if (i >= m_x.size() - 1)
    {
        addData(m_xPos, m_y[i]);
        i = 0;
        m_xPos += m_x[i+1] - m_x[i];
        if (m_xPos >= keyAxis()->range().upper)
        {
            addData(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }
        m_xPos = fmod(m_xPos, keyAxis()->range().upper);
    }
    else {
        addData(m_xPos, m_y[i]);
        m_xPos += m_x[i+1] - m_x[i];
        if (m_xPos >= keyAxis()->range().upper)
        {
            addData(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }
        m_xPos = fmod(m_xPos, keyAxis()->range().upper);
        i += 1;
    }

    removeData(m_xPos, m_xPos + m_dt);
}

void Signal::removeData(double x0, double x1)
{
    if (x1 > keyAxis()->range().upper)
    {
        x1 = fmod(x1, keyAxis()->range().upper);

        for (int i = 0; i < data()->size(); i++)
        {
            auto dp = data()->at(i);
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
            auto dp = data()->at(i);
            if (dp->mainKey() >= x0 && dp->mainKey() <= x1)
            {
                data()->remove(dp->sortKey());
            }

        }
    }
}
