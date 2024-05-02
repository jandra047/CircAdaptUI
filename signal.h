#ifndef SIGNAL_H
#define SIGNAL_H
#include <qcustomplot.h>

class Signal : public QCPCurve
{
public:
    Signal(QCPAxis*, QCPAxis*);
    void updateGraph();
    void removeData(double, double);
    void setXData(QVector<double>& x) {m_x = x;};
    void setYData(QVector<double>& y) {m_y = y;};


private:
    QVector<double> m_x;
    QVector<double> m_y;
    double m_xPos;
    int i;
    double m_dt;
};

#endif // SIGNAL_H
