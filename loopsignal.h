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
    void setXData(QVector<double>const & x) {m_x = x;};
    void setYData(QVector<double>const & y) {m_y = y;};
    void setTData(QVector<double>const & t) {m_t = t;};
    void removeData(double const, double);

private:
    QString m_name;
    QVector<double> m_x;
    QVector<double> m_y;
    QVector<double> m_t;
    int i{0};
    double m_dt{0.1};
};

#endif // LOOPSIGNAL_H
