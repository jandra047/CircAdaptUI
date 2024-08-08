#include "svgheartobject.h"
#include <QPen>

SVGHeartObject::SVGHeartObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", parent),
    aorticValve(QPointF(74.8, 86.0), this),
    mitralValve(QPointF(74.8, 61.0), this),
    tricuspidValve(QPointF(44.5, 61.0), this),
    pulmonaryValve(QPointF(44.5, 86.0), this)
{
    subMenuContainer->addButton("Valves");
    subMenuContainer->addButton("Shunts");
    subMenuContainer->addButton("Pericardium");

    subMenuContainer->buttonGroup->buttons()[0]->setChecked(true);

}
