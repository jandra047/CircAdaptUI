#include "buffer.h"

Buffer::Buffer()
{
    m_beatData.reserve(2);
    for (int i = 0; i < 2; i++)
    {
        m_beatData.push_back(new BeatData);
    }

}

void Buffer::append(const QString& string, double value)
{
    QMutexLocker l(&mutex);
    m_data[string].append(value);
    m_currentBeatData[string].append(value);
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

void Buffer::clear(double dt)
{
    QMutexLocker l(&mutex);
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
}

void Buffer::runAfterBeat()
{
    if (m_beatData.count() >= 2)
        m_beatData.first()->clear();
    m_beatData.last()->setData(m_currentBeatData);
    m_currentBeatData.clear();

    emit updateValueView(m_beatData.last()->getStats());
}
