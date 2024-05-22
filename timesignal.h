#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H
#include <qcustomplot.h>
#include "buffer.h"

class TimeSignal : public QCPGraph
{

public:
    TimeSignal(QCPAxis* xAxis, QCPAxis* yAxis, QString name) : QCPGraph(xAxis, yAxis), m_name(name)
    {
        setPen(QPen(Qt::black, 2));
    };
    void updateGraph(Buffer&);
    void removeData(double, double);


private:
    QString m_name;
    double m_xPos{0};
    int i{0};
    double m_dt{0.1};
};

#endif // TIMESIGNAL_H
