#include "svgtorsoobject.h"
#include <QWidget>

SVGTorsoObject::SVGTorsoObject(QGraphicsItem* parent):
    SVGObjectBase(":/CircAdapt/svgs/Full_Body.svg", parent)
{
    createSceneSwitch("Systemic");
    createSceneSwitch("Pulmonary");
}
