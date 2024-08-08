#ifndef SVGHEARTOBJECT_H
#define SVGHEARTOBJECT_H

#include "svgobjectbase.h"

class SVGHeartObject : public SVGObjectBase
{
public:
    SVGHeartObject(QGraphicsItem* parent = Q_NULLPTR);

    QGraphicsItemGroup* valveGroup;
    QGraphicsItemGroup* shuntGroup;

};

#endif // SVGHEARTOBJECT_H
