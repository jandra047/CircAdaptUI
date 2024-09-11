#ifndef LOOPMARKER_H
#define LOOPMARKER_H

#include "qcustomplot.h"

class LoopMarker : public QCPItemEllipse
{
public:
    LoopMarker(QCustomPlot* parent) :
        QCPItemEllipse(parent),
        m_circleRadius(8.0),
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
    void setColor(QColor color) { m_color = color; }
    void setThickness(double thickness) { m_thickness = thickness; }


private:
    double m_circleRadius;
    double m_circleThickness;
    double m_keyPos;
    double m_valuePos;
    QColor m_color;
    double m_thickness;
};

#endif // LOOPMARKER_H
