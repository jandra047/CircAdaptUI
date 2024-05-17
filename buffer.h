#ifndef BUFFER_H
#define BUFFER_H
// #include <QQueue>
// #include <QMap>

// class Buffer : public QMap<QString, QQueue<double>>
// {
// public:
//     Buffer() : QMap<QString, QQueue<double>> () {
//             this["pLv"].enqueue
//         };

// private:
//     QQueue<double> pLv;
//     QQueue<double> t;
// };

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
    QMap<QString, QVector<double>> data;

};



#endif // BUFFER_H
