#include "svgtissueobject.h"

SVGTissueObject::SVGTissueObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart_segments.svg", parent)
{
    createSceneSwitch("Right atrium");
    createSceneSwitch("Left atrium");
    createSceneSwitch("Rv free wall");
    createSceneSwitch("Septal wall");
    createSceneSwitch("Lv free wall");

}
