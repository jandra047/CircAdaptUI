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
               QString unit = "",
               bool isInMainMenu = true) :
        QCPCurve(xAxis, yAxis),
        m_yVar(yVar),
        m_xVar(xVar),
        m_displayName(displayName),
        color(color),
        m_unit(unit),
        m_isInMainMenu(isInMainMenu),
        m_marker(Q_NULLPTR)
    {
        setVisible(isVisible);
        setPen(QPen(color, 1));
    };

    ~LoopSignal() = default;

    LoopSignal(const LoopSignal& other)
        : QCPCurve(other.parentPlot()->xAxis, other.parentPlot()->yAxis),
        m_yVar(other.m_yVar),
        m_xVar(other.m_xVar),
        m_displayName(other.m_displayName),
        color(other.color),
        m_unit(other.m_unit),
        i(other.i),
        m_dt(other.m_dt),
        m_isInMainMenu(other.m_isInMainMenu),
        m_marker(Q_NULLPTR)
    {
        setVisible(other.visible());
        setPen(QPen(color, 1));
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
            m_isInMainMenu = other.m_isInMainMenu;

            setVisible(other.visible());
            setPen(QPen(color, 1));
        }
        return *this;
    }

    void updateGraph(Buffer& buffer, double timeInterval);
    void removeData(double const x0, double x1, Buffer& buffer);
    const QString getXVar() const { return m_xVar; };
    const QString getYVar() const { return m_yVar; };
    const QColor getColor() const { return color; }
    const QString getDisplayName() const { return m_displayName; }
    const QString getUnit() const { return m_unit; }
    const bool isInMainMenu() const { return m_isInMainMenu; }
    const double getXPos() const { return 0; }
    LoopMarker* getMarker() { return m_marker; }
    void createMarker();
    void setVisible(bool isVisible);
    void reset();
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
    bool m_isInMainMenu;
};

#endif // LOOPSIGNAL_H
