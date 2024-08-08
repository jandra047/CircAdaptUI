#include "valveelement.h"

ValveElement::ValveElement(QPointF center, QGraphicsObject* parent):
    GraphicElement(parent),
    mCenter(center)
{
    mPath.addEllipse(mCenter.x() - (6/2),
                     mCenter.y() - (6/2),
                     6,
                     6);

    setPath(mPath);
}
