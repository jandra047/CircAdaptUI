#ifndef LOOPMARKER_H
#define LOOPMARKER_H

#include "qcustomplot.h"

class LoopMarker : public QCPItemEllipse
{
public:
    LoopMarker(QCustomPlot* parent) :
        QCPItemEllipse(parent),
        m_circleRadius(6.0),
        m_circleThickness(2.5)
    {
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
    double m_circleRadius;
    double m_circleThickness;
    double m_keyPos;
    double m_valuePos;
};

#endif // LOOPMARKER_H
