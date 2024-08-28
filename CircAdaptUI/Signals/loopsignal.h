#ifndef LOOPSIGNAL_H
#define LOOPSIGNAL_H
#include "dependencies/qcustomplot.h"
#include "CircAdaptUI/buffer.h"

class LoopSignal : public QCPCurve
{
public:
    LoopSignal(QCPAxis* xAxis,
               QCPAxis* yAxis,
               QString displayName,
               QString yVar,
               QString xVar,
               QColor color = QColor(0,0,0),
               bool isVisible = true,
               QString unit = "") :
        QCPCurve(xAxis, yAxis),
        m_yVar(yVar),
        m_xVar(xVar),
        m_displayName(displayName),
        color(color),
        m_unit(unit)
    {
        setVisible(isVisible);
        setPen(QPen(color, 2));
    };
    ~LoopSignal() {};
    void updateGraph(Buffer& buffer);
    void removeData(double const x0, double x1, Buffer& buffer);
    QString getXVar() { return m_xVar; };
    QString getYVar() { return m_yVar; };
    QColor getColor() { return color; }
    QString getDisplayName() { return m_displayName; }
    QString getUnit() { return m_unit; }

private:
    QString m_yVar;
    QString m_xVar;
    int i{0};
    double m_dt{0.2};
    QColor color;
    QString m_displayName;
    QString m_unit;
};

#endif // LOOPSIGNAL_H
