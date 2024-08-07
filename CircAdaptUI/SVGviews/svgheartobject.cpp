#include "svgheartobject.h"

SVGHeartObject::SVGHeartObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", parent)
{
    createSceneSwitch("Valves");
    createSceneSwitch("Shunts");
    createSceneSwitch("Pericardium");
}
