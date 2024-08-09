#include "svgtorsoobject.h"
#include <QWidget>
#include <QPen>

SVGTorsoObject::SVGTorsoObject(QGraphicsItem* parent):
    SVGObjectBase(":/CircAdapt/svgs/Full_Body.svg", "", parent)
{
    subMenuContainer->addButton("Systemic circulation");
    subMenuContainer->addButton("Pulmonary circulation");

    subMenuContainer->buttonGroup->buttons().at(0)->setChecked(true);

    createCovers();
    showSystemic();
    connect(subMenuContainer->buttonGroup, &QButtonGroup::buttonClicked, this, &SVGTorsoObject::handleSubMenuSwitch);
}

void SVGTorsoObject::handleSubMenuSwitch(QAbstractButton* button)
{
    if (button->text() == "Systemic circulation")
    {
        showSystemic();
    }
    else
    {
        showPulmonary();
    }

}

void SVGTorsoObject::showSystemic()
{
    coverSystemic->setVisible(false);
    coverPulmonary->setVisible(true);
}

void SVGTorsoObject::showPulmonary()
{
    coverSystemic->setVisible(true);
    coverPulmonary->setVisible(false);
}

void SVGTorsoObject::createCovers()
{
    QBrush coverBrush(QColor(255, 255, 255, 200), Qt::SolidPattern);
    coverSystemic = new QGraphicsRectItem(0, 0, m_bgItem.boundingRect().width() / 2.0, m_bgItem.boundingRect().height(), this);
    coverSystemic->setBrush(coverBrush);
    coverSystemic->setPen(Qt::NoPen);
    coverSystemic->setZValue(100);
    coverPulmonary = new QGraphicsRectItem(m_bgItem.boundingRect().width() / 2.0, 0, m_bgItem.boundingRect().width() / 2.0, m_bgItem.boundingRect().height(), this);
    coverPulmonary->setBrush(coverBrush);
    coverPulmonary->setPen(Qt::NoPen);
    coverPulmonary->setZValue(100);
}


