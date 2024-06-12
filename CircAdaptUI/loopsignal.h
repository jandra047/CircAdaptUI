#ifndef LOOPSIGNAL_H
#define LOOPSIGNAL_H
#include "qcustomplot.h"
#include "buffer.h"

class LoopSignal : public QCPCurve
{
public:
    LoopSignal(QCPAxis* xAxis, QCPAxis* yAxis, QString yVar, QString xVar, QColor color = QColor(0,0,0)) :
        QCPCurve(xAxis, yAxis),
        m_yVar(yVar),
        m_xVar(xVar)
    {
        setPen(QPen(color, 2));
    };
    void updateGraph(Buffer& buffer);
    void removeData(double const x0, double x1);

private:
    QString m_yVar;
    QString m_xVar;
    int i{0};
    double m_dt{0.2};
};

#endif // LOOPSIGNAL_H
