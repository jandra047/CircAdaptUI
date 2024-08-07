#include "svgheartobject.h"

SVGHeartObject::SVGHeartObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", parent)
{
    subMenuContainer->addButton("Valves");
    subMenuContainer->addButton("Shunts");
    subMenuContainer->addButton("Pericardium");
}
