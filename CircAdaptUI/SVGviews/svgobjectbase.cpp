#include "svgobjectbase.h"
#include <QSvgRenderer>

SVGObjectBase::SVGObjectBase(const QString& bgImg, QGraphicsItem* parent) :
    QGraphicsObject(parent),
    m_bgItem(QGraphicsSvgItem(bgImg, this))
{
    QSvgRenderer* renderer = new QSvgRenderer(bgImg, this);
    m_bgItem.setSharedRenderer(renderer);
    m_bgItem.setActive( true );
    m_bgItem.setVisible( true );
    m_bgItem.show();
    m_bgItem.setZValue( 1 );
}

QRectF SVGObjectBase::boundingRect( void ) const
{
    // This base class is only meant as a container of all dynamic object in a model view group. The
    // rectangle to return is a dummy one and not needed to deterine the items extent. Return just a
    // valid value
    return QRectF( 0.0, 0.0, 1.0, 1.0 );
}


void SVGObjectBase::paint( QPainter *, const QStyleOptionGraphicsItem *, QWidget * )
{
    // This base class is only meant as a container of all dynamic object in a model view group. Nothing
    // needs to be visualized, so nothing to paint
}
