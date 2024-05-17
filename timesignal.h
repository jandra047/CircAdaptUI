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
    void updateGraph();
    void updateGraph2(Buffer& buffer);
    void removeData(double, double);
    void setYData(QVector<double>const & y) {m_y = y;};
    void setTData(QVector<double>const & t) {m_t = t;};
    void addYData(double const & y) {m_y.push_back(y);};
    void addTData(double const & t) {m_t.push_back(t);};


private:
    QString m_name;
    QVector<double> m_y{};
    QVector<double> m_t{};
    double m_xPos{0};
    int i{0};
    double m_dt{0.1};
};

#endif // TIMESIGNAL_H
