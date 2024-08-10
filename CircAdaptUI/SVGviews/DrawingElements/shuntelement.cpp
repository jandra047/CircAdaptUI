#include "shuntelement.h"
#include <QSvgRenderer>

ShuntElement::ShuntElement(const QPointF& point, QGraphicsObject* parent):
    GraphicElement(parent)
{
    GraphicElement::parsePathDataFast(arrow, mPath);
    mPath.translate(point);
    setPath(mPath);
}
