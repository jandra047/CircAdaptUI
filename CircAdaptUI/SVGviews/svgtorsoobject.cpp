#include "svgtorsoobject.h"
#include <QWidget>

SVGTorsoObject::SVGTorsoObject(QGraphicsItem* parent):
    SVGObjectBase(":/CircAdapt/svgs/Full_Body.svg", parent)
{
    subMenuContainer->addButton("Systemic circulation");
    subMenuContainer->addButton("Pulmonary circulation");
}
