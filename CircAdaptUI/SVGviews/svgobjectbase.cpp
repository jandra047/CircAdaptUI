#include "svgobjectbase.h"
#include <QSvgRenderer>

#include <QWidget>
#include <QHBoxLayout>

SVGObjectBase::SVGObjectBase(const QString& bgImg, QGraphicsItem* parent) :
    QGraphicsObject(parent),
    m_bgItem(QGraphicsSvgItem(bgImg, this)),
    subMenuContainer(new ToggleButtonGroup())
{
    QSvgRenderer* renderer = new QSvgRenderer(bgImg, this);
    m_bgItem.setSharedRenderer(renderer);
    m_bgItem.setElementId(""); // Ensure we're rendering the whole SVG
    QRectF bounds = renderer->viewBoxF();
    m_bgItem.setPos(0, 0);
    m_bgItem.setScale(1.0);
    m_bgItem.setActive( true );
    m_bgItem.setVisible( true );
    m_bgItem.show();
    m_bgItem.setZValue( 1 );
}

QRectF SVGObjectBase::boundingRect() const
{
    return m_bgItem.boundingRect();
}

void SVGObjectBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    m_bgItem.paint(painter, option, widget);
}
