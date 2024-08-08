#include "graphicelement.h"

GraphicElement::GraphicElement(QGraphicsObject* parent):
    QGraphicsPathItem(parent),
    m_Pen(Qt::black),
    m_Brush(Qt::gray)
{
    m_Pen.setWidthF(0.5);
    setPen(m_Pen);
    setBrush(m_Brush);
    setZValue(1);
}
