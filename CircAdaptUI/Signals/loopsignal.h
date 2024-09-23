#ifndef LOOPSIGNAL_H
#define LOOPSIGNAL_H
#include "dependencies/qcustomplot.h"
#include "CircAdaptUI/buffer.h"

class LoopMarker;

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
        m_unit(unit),
        m_marker(Q_NULLPTR)
    {
        setVisible(isVisible);
        setPen(QPen(color, 2));
    };

    ~LoopSignal();

    LoopSignal(const LoopSignal& other)
        : QCPCurve(other.parentPlot()->xAxis, other.parentPlot()->yAxis),
        m_yVar(other.m_yVar),
        m_xVar(other.m_xVar),
        m_displayName(other.m_displayName),
        color(other.color),
        m_unit(other.m_unit),
        i(other.i),
        m_dt(other.m_dt),
        m_marker(Q_NULLPTR)
    {
        setVisible(other.visible());
        setPen(QPen(color, 2));
    }

    LoopSignal& operator=(const LoopSignal& other)
    {
        if (this != &other)
        {
            m_yVar = other.m_yVar;
            m_xVar = other.m_xVar;
            m_displayName = other.m_displayName;
            color = other.color;
            m_unit = other.m_unit;
            i = other.i;
            m_dt = other.m_dt;
            m_marker = Q_NULLPTR;

            setVisible(other.visible());
            setPen(QPen(color, 2));
        }
        return *this;
    }

    void updateGraph(Buffer& buffer);
    void removeData(double const x0, double x1, Buffer& buffer);
    QString getXVar() { return m_xVar; };
    QString getYVar() { return m_yVar; };
    QColor getColor() { return color; }
    QString getDisplayName() { return m_displayName; }
    QString getUnit() { return m_unit; }
    LoopMarker* getMarker() { return m_marker; }
    void createMarker();
    void setVisible(bool isVisible);
    void clear();

private:
    QString m_yVar;
    QString m_xVar;
    int i{0};
    double m_dt{0.2};
    QColor color;
    QString m_displayName;
    QString m_unit;
    LoopMarker* m_marker;
};

#endif // LOOPSIGNAL_H
