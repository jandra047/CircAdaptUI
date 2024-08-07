#include "svgtorsoobject.h"
#include <QWidget>

SVGTorsoObject::SVGTorsoObject(QGraphicsItem* parent):
    SVGObjectBase(":/CircAdapt/svgs/Full_Body.svg", parent)
{
    createSceneSwitch("Systemic circulation");
    createSceneSwitch("Pulmonary circulation");
}
