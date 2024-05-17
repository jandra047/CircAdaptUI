#include "buffer.h"

Buffer::Buffer() {}

void Buffer::append(const QString& string, double value)
{
    data[string].append(value);
}

QVector<double> Buffer::take(const QString& string, double dt)
{
    int count = 0;
    QVector<double>& vec = data[string];
    for (int i = 0; i < data["t"].size(); i++) {
        if (qAbs(data["t"][i] - data["t"][0]) <= dt) {
            ++count;
        }
        else break;
    }

    QVector<double> out;
    out.reserve(count);
    std::move(vec.begin(),
              vec.begin() + count,
              std::back_inserter(out));

    // Erase the moved elements from originalVector
    vec.erase(vec.begin(), vec.begin() + count);
    return out;
}

QVector<double> Buffer::get(const QString& string, double dt)
{
    int count = 0;
    QVector<double>& vec = data[string];
    for (int i = 0; i < data["t"].size(); i++) {
        if (qAbs(data["t"][i] - data["t"][0]) <= dt) {
            ++count;
        }
        else break;
    }

    QVector<double> out;
    out.reserve(count);
    std::copy(vec.begin(), vec.begin() + count, std::back_inserter(out));
    return out;

}
