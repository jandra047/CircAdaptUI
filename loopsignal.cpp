#include "loopsignal.h"

namespace {
    auto const quiet_nan = std::numeric_limits<double>::quiet_NaN();
}

void LoopSignal::updateGraph()
{
    addData(m_t[i], m_x[i], m_y[i]);
    i %= m_x.size() - 1;
    i += 1;
    data()->remove(m_t[i], m_t[i] + m_dt);
    addData(m_t[i] + m_dt, m_t[i] + m_dt, quiet_nan);
}
