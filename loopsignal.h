#ifndef LOOPSIGNAL_H
#define LOOPSIGNAL_H
#include <qcustomplot.h>
#include "buffer.h"

class LoopSignal : public QCPCurve
{
public:
    LoopSignal(QCPAxis* xAxis, QCPAxis* yAxis, QString name) : QCPCurve(xAxis, yAxis), m_name(name)
    {
        setPen(QPen(Qt::black, 2));
    };
    void updateGraph(Buffer& buffer);
    void removeData(double const, double);

private:
    QString m_name;
    int i{0};
    double m_dt{0.1};
};

#endif // LOOPSIGNAL_H
