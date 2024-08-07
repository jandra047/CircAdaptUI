#include "svgtissueobject.h"

SVGTissueObject::SVGTissueObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart_segments.svg", parent)
{
    subMenuContainer->addButton("Right atrium");
    subMenuContainer->addButton("Left atrium");
    subMenuContainer->addButton("Rv free wall");
    subMenuContainer->addButton("Septal wall");
    subMenuContainer->addButton("Lv free wall");

}
