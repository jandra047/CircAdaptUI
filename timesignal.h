#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H
#include <qcustomplot.h>
#include "buffer.h"

class TimeSignal : public QCPGraph
{

public:
    TimeSignal(QCPAxis* xAxis, QCPAxis* yAxis, QString yVar, QString xVar = "t") :
        QCPGraph(xAxis, yAxis),
        m_yVar(yVar),
        m_xVar(xVar)
    {
        setPen(QPen(Qt::black, 2));
    };
    void updateGraph(Buffer&);
    void removeData(double, double);


private:
    QString m_yVar;
    QString m_xVar;
    double m_xPos{0};
    int i{0};
    double m_dt{0.1};
};

#endif // TIMESIGNAL_H
