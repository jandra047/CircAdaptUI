#ifndef SIGNAL_H
#define SIGNAL_H
#include <qcustomplot.h>

class Signal : public QCPCurve
{
public:
    Signal(QCPAxis* xAxis, QCPAxis* yAxis) : QCPCurve(xAxis, yAxis) {};
    void updateGraph();
    void removeData(double, double);
    void setXData(QVector<double>const & x) {m_x = x;};
    void setYData(QVector<double>const & y) {m_y = y;};


private:
    QVector<double> m_x;
    QVector<double> m_y;
    double m_xPos{0};
    int i{0};
    double m_dt{0.2};
};

#endif // SIGNAL_H
