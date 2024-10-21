#include "svgheartobject.h"
#include <QPen>
#include <QGraphicsScene>
#include "DrawingElements/valveelement.h"
#include "DrawingElements/shuntelement.h"
#include "DrawingElements/textcircle.h"
#include "CircAdaptUI/settings.h"

SVGHeartObject::SVGHeartObject(PropertyBrowserBase* propertyBrowser, QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart.svg", propertyBrowser, "layer1", parent),
    valveGroup(new DrawingElementGroup(this)),
    shuntGroup(new DrawingElementGroup(this)),
    oxygenGroup(new DrawingElementGroup(this))
{

    subMenuContainer->addButton("Valves");
    subMenuContainer->addButton("Shunts");
    subMenuContainer->addButton("Pericardium");

    propertyMap = propertyBrowser->createProperties(Settings::instance().ModelParameters()["Heart"].toObject());

    valveGroup->addToGroup(new ValveElement("Tricuspid valve", QPointF(44.5, 61.0), this));
    valveGroup->addToGroup(new ValveElement("Pulmonary valve", QPointF(44.5, 86.0), this));
    valveGroup->addToGroup(new ValveElement("Mitral valve", QPointF(74.8, 61.0), this));
    valveGroup->addToGroup(new ValveElement("Aortic valve", QPointF(74.8, 86.0), this));
    valveGroup->selectElement(valveGroup->childItems().at(0));
    valveGroup->setZValue(1);

    shuntGroup->addToGroup(new ShuntElement("Atrial septal defect", QPointF(-39, -36.5), this));
    shuntGroup->addToGroup(new ShuntElement("Ventricular septal defect", QPointF(-39, -13.5), this));
    shuntGroup->selectElement(shuntGroup->childItems().at(0));
    shuntGroup->setZValue(1);

    oxygenGroup->addToGroup(new TextCircle("satSyVen", QPointF(44.5, 15.0), this));
    oxygenGroup->addToGroup(new TextCircle("satRa", QPointF(44.5, 50.0), this));
    oxygenGroup->addToGroup(new TextCircle("satRv", QPointF(44.5, 75.0), this));
    oxygenGroup->addToGroup(new TextCircle("satPuArt", QPointF(44.5, 115.0), this));
    oxygenGroup->addToGroup(new TextCircle("satPuVen", QPointF(74.8, 15.0), this));
    oxygenGroup->addToGroup(new TextCircle("satLa", QPointF(74.8, 50.0), this));
    oxygenGroup->addToGroup(new TextCircle("satLv", QPointF(74.8, 75.0), this));
    oxygenGroup->addToGroup(new TextCircle("satSyArt", QPointF(74.8, 115.0), this));
    oxygenGroup->setSelectable(false);
    oxygenGroup->setVisible(false);
    oxygenGroup->setZValue(1);

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
    setVisibleProperties(propertyMap["Pericardial sac"]);
}

void SVGHeartObject::showOxygen(bool isVisible)
{
    oxygenGroup->setVisible(isVisible);
}

void SVGHeartObject::updateOxygen(Buffer& buffer)
{
    oxygenGroup->updateText(buffer);
}
