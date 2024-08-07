#include "svgheartobject.h"

SVGHeartObject::SVGHeartObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", parent)
{
    createSceneSwitch("A");
    createSceneSwitch("b");
    createSceneSwitch("c");
}
