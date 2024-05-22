#include "buffer.h"

Buffer::Buffer() {}

void Buffer::append(const QString& string, double value, QMutex& mutex)
{
    mutex.lock();
    m_data[string].append(value);
    mutex.unlock();
}

QVector<double> Buffer::get(const QString& string, double dt)
{
    int count = 0;
    QVector<double>& vec = m_data[string];
    if (!vec.empty())
    {
        for (int i = 0; i < m_data["t"].size(); i++)
        {
            if (qAbs(m_data["t"][i] - m_data["t"][0]) <= dt)
            {
                ++count;
            }
            else break;
        }

        QVector<double> out;
        out.reserve(count);
        std::copy(vec.begin(), vec.begin() + count, std::back_inserter(out));
        return out;
    }
    else
    {
        throw std::range_error(string.toStdString() + " buffer empty!");
    }
}

void Buffer::clear(double dt, QMutex& mutex)
{
    mutex.lock();
    int count = 0;
    for (int i = 0; i < m_data["t"].size(); i++)
    {
        if (qAbs(m_data["t"][i] - m_data["t"][0]) <= dt)
        {
            count++;
        }
        else break;
    }

    for (auto [key, vec] : m_data.asKeyValueRange())
    {
        vec.erase(vec.begin(), vec.begin() + count);
    }
    mutex.unlock();
}
