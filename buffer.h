#ifndef BUFFER_H
#define BUFFER_H

#include <QMap>
#include <QString>
#include <QDebug>
#include <QMutex>

class Buffer
{
public:
    Buffer();
    void append(const QString&, double);
    QVector<double> get(const QString&, double);
    void clear(double);
    int getLen() { QMutexLocker l(&mutex); return m_data["t"].size(); }


private:
    QMap<QString, QVector<double>> m_data;
    QMutex mutex;

};



#endif // BUFFER_H
