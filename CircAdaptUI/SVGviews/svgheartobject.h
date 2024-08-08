#ifndef SVGHEARTOBJECT_H
#define SVGHEARTOBJECT_H

#include "svgobjectbase.h"
#include "DrawingElements/valve.h"

class SVGHeartObject : public SVGObjectBase
{
public:
    SVGHeartObject(QGraphicsItem* parent = Q_NULLPTR);
    Valve mitralValve;
    Valve aorticValve;
    Valve tricuspidValve;
    Valve pulmonaryValve;
};

#endif // SVGHEARTOBJECT_H
