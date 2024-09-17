#include "shuntelement.h"
#include <QSvgRenderer>

ShuntElement::ShuntElement(QString name, const QPointF& point, SVGObjectBase* parent):
    GraphicElement(name, parent)
{
    GraphicElement::parsePathDataFast(arrow, mPath);
    mPath.translate(point);
    setPath(mPath);
    m_penSelected.setWidthF(1.5);
}
