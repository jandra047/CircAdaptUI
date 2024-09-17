#include "valveelement.h"
#include <QGraphicsSceneMouseEvent>

ValveElement::ValveElement(QString name, QPointF center, SVGObjectBase* parent):
    GraphicElement(name, parent),
    mCenter(center)
{
    mPath.addEllipse(mCenter.x() - (6/2),
                     mCenter.y() - (6/2),
                     6,
                     6);

    setPath(mPath);
    m_penSelected.setWidthF(1.5);
}
