#ifndef BUFFER_H
#define BUFFER_H

#include <QMap>
#include <QString>
#include <QDebug>

class Buffer
{
public:
    Buffer();
    void append(const QString&, double);
    QVector<double> take(const QString&, double);
    QVector<double> get(const QString&, double);


private:
    QMap<QString, QVector<double>> m_data;

};



#endif // BUFFER_H
