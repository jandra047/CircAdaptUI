#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H
#include <qcustomplot.h>

class TimeSignal : public QCPGraph
{
public:
    TimeSignal(QCPAxis* xAxis, QCPAxis* yAxis) : QCPGraph(xAxis, yAxis)
    {
        setPen(QPen(Qt::black, 2));
    };
    void updateGraph();
    void removeData(double, double);
    void setYData(QVector<double>const & y) {m_y = y;};
    void setTData(QVector<double>const & t) {m_t = t;};


private:
    QVector<double> m_y;
    QVector<double> m_t;
    double m_xPos{0};
    int i{0};
    double m_dt{0.1};
};

#endif // TIMESIGNAL_H
