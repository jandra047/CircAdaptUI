#include "svgheartobject.h"
#include <QPen>
#include <QGraphicsScene>
#include "DrawingElements/valveelement.h"
#include "DrawingElements/shuntelement.h"

SVGHeartObject::SVGHeartObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", "layer1", parent),
    valveGroup(new QGraphicsItemGroup(this)),
    shuntGroup(new QGraphicsItemGroup(this))
{

    subMenuContainer->addButton("Valves");
    subMenuContainer->addButton("Shunts");
    subMenuContainer->addButton("Pericardium");

    valveGroup->addToGroup(new ValveElement(QPointF(74.8, 86.0), this));
    valveGroup->addToGroup(new ValveElement(QPointF(74.8, 61.0), this));
    valveGroup->addToGroup(new ValveElement(QPointF(44.5, 61.0), this));
    valveGroup->addToGroup(new ValveElement(QPointF(44.5, 86.0), this));
    valveGroup->setZValue(1);

    shuntGroup->addToGroup(new ShuntElement(QPointF(-39, -36.5), this));
    shuntGroup->addToGroup(new ShuntElement(QPointF(-39, -13.5), this));
    shuntGroup->setZValue(1);

    subMenuContainer->buttonGroup->buttons().at(0)->setChecked(true);
    showValves();

    connect(subMenuContainer->buttonGroup, &QButtonGroup::buttonClicked, this, &SVGHeartObject::handleSubMenuSwitch);

}

void SVGHeartObject::handleSubMenuSwitch(QAbstractButton* button)
{
    if (button->text() == "Valves")
    {
        showValves();
    }
    else if (button->text() == "Shunts")
    {
        showShunts();
    }
    else
    {
        showPericardium();
    }
}

void SVGHeartObject::showValves()
{
    valveGroup->setVisible(true);
    shuntGroup->setVisible(false);
    m_bgItem.setElementId("layer1");
}

void SVGHeartObject::showShunts()
{
    valveGroup->setVisible(false);
    shuntGroup->setVisible(true);
    m_bgItem.setElementId("layer1");
}

void SVGHeartObject::showPericardium()
{
    valveGroup->setVisible(false);
    shuntGroup->setVisible(false);
    m_bgItem.setElementId("");
}
