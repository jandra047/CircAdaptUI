#ifndef VALVEELEMENT_H
#define VALVEELEMENT_H

#include "graphicelement.h"

class ValveElement : public GraphicElement
{
public:
    ValveElement(QString name, QPointF center, SVGObjectBase* parent = Q_NULLPTR);

    QPointF mCenter;
    QPainterPath mPath;
};

#endif // VALVEELEMENT_H
