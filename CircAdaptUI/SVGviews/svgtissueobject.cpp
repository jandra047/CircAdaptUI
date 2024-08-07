#include "svgtissueobject.h"

SVGTissueObject::SVGTissueObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart_segments.svg", parent)
{
    createSceneSwitch("S");
    createSceneSwitch("ssS");
    createSceneSwitch("aS");

}
