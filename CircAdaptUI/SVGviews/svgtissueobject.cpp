#include "svgtissueobject.h"

SVGTissueObject::SVGTissueObject(QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart_segments.svg", "", parent),
    rightAtrium(new RightAtrium(this)),
    leftAtrium(new LeftAtrium(this)),
    rightVentricle(new RightVentricle(this)),
    septum(new Septum(this)),
    leftVentricle(new LeftVentricle(this))
{
    subMenuContainer->addButton("Right atrium");
    subMenuContainer->addButton("Left atrium");
    subMenuContainer->addButton("Rv free wall");
    subMenuContainer->addButton("Septal wall");
    subMenuContainer->addButton("Lv free wall");

    subMenuContainer->buttonGroup->buttons().at(0)->setChecked(true);

    m_CoverElement = new QGraphicsRectItem(m_bgItem.boundingRect(), this);
    QColor  coverColor( 255, 255, 255, 200 );
    QBrush  coverBrush( coverColor, Qt::SolidPattern );

    m_CoverElement->setPen( Qt::NoPen );    // Draw no outline
    m_CoverElement->setBrush( coverBrush );
    m_CoverElement->setZValue( 5.0 );      // Make sure it will be drawn below the seperate active tissue layers

    showView(ViewType::Ra);
    connect(subMenuContainer->buttonGroup, &QButtonGroup::buttonClicked, this, &SVGTissueObject::handleSubMenuSwitch);
}

void SVGTissueObject::showView(const ViewType& viewType)
{
    rightAtrium->setSelected(viewType == ViewType::Ra ? true : false);
    leftAtrium->setSelected(viewType == ViewType::La ? true : false);
    rightVentricle->setSelected(viewType == ViewType::Rv ? true : false);
    septum->setSelected(viewType == ViewType::Sv ? true : false);
    leftVentricle->setSelected(viewType == ViewType::Lv ? true : false);
}

void SVGTissueObject::handleSubMenuSwitch(QAbstractButton* button)
{
    if (button->text() == "Right atrium")
    {
        showView(ViewType::Ra);
    }
    if (button->text() == "Left atrium")
    {
        showView(ViewType::La);
    }
    if (button->text() == "Rv free wall")
    {
        showView(ViewType::Rv);
    }
    if (button->text() == "Septal wall")
    {
        showView(ViewType::Sv);
    }
    if (button->text() == "Lv free wall")
    {
        showView(ViewType::Lv);
    }
}
