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
    void append(const QString&, double, QMutex&);
    QVector<double> get(const QString&, double);
    void clear(double, QMutex&);


private:
    QMap<QString, QVector<double>> m_data;

};



#endif // BUFFER_H
