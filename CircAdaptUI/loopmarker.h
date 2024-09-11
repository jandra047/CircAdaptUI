#ifndef LOOPMARKER_H
#define LOOPMARKER_H

#include "qcustomplot.h"
#include "CircAdaptUI/Signals/loopsignal.h"

class LoopMarker : public QCPItemEllipse
{
public:
    LoopMarker(LoopSignal* signal) :
        QCPItemEllipse(signal->parentPlot()),
        m_signal(signal),
        m_circleRadius(8.0),
        m_circleThickness(2.5)
    {
        QPen pen = m_signal->pen();
        QColor color = pen.color();
        color.setAlphaF(0.7);
        pen.setColor(color);
        setPen(pen);
        setVisible(false);
    }

    LoopMarker(const LoopMarker& other) :
        QCPItemEllipse(other.parentPlot()),
        m_circleRadius(other.m_circleRadius),
        m_circleThickness(other.m_circleThickness)
    {
        setPen(other.pen());
        setBrush(other.brush());
        setVisible(false);
    }

    LoopMarker& operator=(const LoopMarker& other)
    {
        if (this != &other)
        {
            m_circleRadius = other.m_circleRadius;
            m_circleThickness = other.m_circleThickness;
            m_keyPos = other.m_keyPos;
            m_valuePos = other.m_valuePos;
        }
        return *this;
    }

    void draw(QCPPainter* painter) override;
    void setPosition(double key, double value);


private:
    LoopSignal* m_signal;
    double m_circleRadius;
    double m_circleThickness;
    double m_keyPos;
    double m_valuePos;
};

#endif // LOOPMARKER_H
