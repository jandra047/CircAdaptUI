#include "graphicelement.h"

GraphicElement::GraphicElement(QGraphicsObject* parent):
    QGraphicsPathItem(parent),
    m_penDefault(Qt::black),
    m_penSelected(Qt::black),
    m_Brush(Qt::gray),
    m_isSelected(false)
{
    m_penDefault.setWidthF(0.5);
    m_penSelected.setWidthF(2);
    setPen(m_penDefault);
    setBrush(m_Brush);
    setZValue(1);

}

void GraphicElement::setSelected(bool isSelected)
{
    m_isSelected = isSelected;

    if (m_isSelected) {
        setPen(m_penSelected);
    }
    else
    {
        setPen(m_penDefault);
    }
}

void GraphicElement::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    setSelected(true);

    QGraphicsPathItem::mousePressEvent(event);
}
