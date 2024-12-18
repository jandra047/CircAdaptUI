#ifndef LOOPSIGNAL_H
#define LOOPSIGNAL_H
#include "dependencies/qcustomplot.h"
#include "signalinterface.h"

class LoopMarker;

class LoopSignal : public QCPCurve, public SignalInterface
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
        SignalInterface(
              displayName,
              yVar,
              xVar,
              color,
              isVisible,
              unit,
              isInMainMenu),
        m_marker(Q_NULLPTR)
    {
        setVisible(isVisible);
        setPen(QPen(color, 2));
    };

    ~LoopSignal() = default;

    LoopSignal(const LoopSignal& other)
        : QCPCurve(other.parentPlot()->xAxis, other.parentPlot()->yAxis),
        SignalInterface(
              other.m_displayName,
              other.m_yVar,
              other.m_xVar,
              other.color,
              other.visible(),
              other.m_unit,
              other.m_isInMainMenu),
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
            m_isInMainMenu = other.m_isInMainMenu;

            setVisible(other.visible());
            setPen(QPen(color, 2));
        }
        return *this;
    }

    void updateGraph(Buffer& buffer, double timeInterval) override;
    void reset() override;
    void removeData(double const x0, double x1, Buffer& buffer);
    LoopMarker* getMarker() { return m_marker; }
    void createMarker();
    void setVisible(bool isVisible);
    void clear();

private:
    LoopMarker* m_marker;
};

#endif // LOOPSIGNAL_H
