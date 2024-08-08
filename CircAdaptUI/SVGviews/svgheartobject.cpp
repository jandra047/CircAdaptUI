#include "svgheartobject.h"
#include <QPen>
#include <QGraphicsScene>
#include "DrawingElements/valveelement.h"
#include "DrawingElements/shuntelement.h"

SVGHeartObject::SVGHeartObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", parent),
    valveGroup(new QGraphicsItemGroup(this)),
    shuntGroup(new QGraphicsItemGroup(this))
{

    subMenuContainer->addButton("Valves");
    subMenuContainer->addButton("Shunts");
    subMenuContainer->addButton("Pericardium");

    subMenuContainer->buttonGroup->buttons().at(0)->setChecked(true);

    valveGroup->addToGroup(new ValveElement(QPointF(74.8, 86.0), this));
    valveGroup->addToGroup(new ValveElement(QPointF(74.8, 61.0), this));
    valveGroup->addToGroup(new ValveElement(QPointF(44.5, 61.0), this));
    valveGroup->addToGroup(new ValveElement(QPointF(44.5, 86.0), this));
    valveGroup->setZValue(1);

    shuntGroup->addToGroup(new ShuntElement(QPointF(-39, -36.5), this));
    shuntGroup->addToGroup(new ShuntElement(QPointF(-39, -13.5), this));
    shuntGroup->setZValue(1);

}
