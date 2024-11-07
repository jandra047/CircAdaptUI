#include "svgtissueobject.h"
#include "CircAdaptUI/settings.h"

SVGTissueObject::SVGTissueObject(PropertyBrowserBase* propertyBrowser, QGraphicsItem* parent) :
    SVGObjectBase(":/CircAdapt/svgs/Heart_segments.svg", propertyBrowser, "", parent),
    rightAtrium(new RightAtrium(this)),
    leftAtrium(new LeftAtrium(this)),
    rightVentricle(new RightVentricle(this)),
    septum(new Septum(this)),
    leftVentricle(new LeftVentricle2(this))
{
    subMenuContainer->addButton("Right atrium");
    subMenuContainer->addButton("Left atrium");
    subMenuContainer->addButton("Rv free wall");
    subMenuContainer->addButton("Septal wall");
    subMenuContainer->addButton("Lv free wall");

    subMenuContainer->buttonGroup->buttons().at(0)->setChecked(true);

    createProperties();

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

void SVGTissueObject::createProperties()
{
    QJsonObject object = Settings::instance().ModelParameters()["Tissue"].toObject();
    QJsonObject newObject;
    qDebug() << object.keys();
    for (auto key : object.keys())
    {
        newObject.insert(key, object[key]);

        if (key == "Left ventricular wall")
        {
            QList<QString> patchNames = leftVentricle->patchNames();
            for (int i = 0; i < 11; ++i)
            {
                QJsonArray modifiedArray;
                for (const auto& value : object[key].toArray())
                {
                    QJsonObject item = value.toObject();
                    QString modifiedKey = item["key"].toString() + " " + QString::number(i);
                    item["key"] = modifiedKey;
                    modifiedArray.append(item);
                }
                // Add to new QJsonObject with updated key names
                newObject.insert(patchNames[i], modifiedArray);
            }

        }
        if (key == "Septal wall")
        {
            for (int i = 0; i < 5; ++i)
            {
                QJsonArray modifiedArray;
                for (const auto& value : object[key].toArray())
                {
                    QJsonObject item = value.toObject();
                    QString modifiedKey = item["key"].toString() + " " + QString::number(i);
                    item["key"] = modifiedKey;
                    modifiedArray.append(item);
                }
                // Add to new QJsonObject with updated key names
                newObject.insert(key + " " + QString::number(i), modifiedArray);
            }
        }
        if (key == "Right ventricular wall")
        {

            for (int i = 0; i < 7; ++i)
            {
                QJsonArray modifiedArray;
                for (const auto& value : object[key].toArray())
                {
                    QJsonObject item = value.toObject();
                    QString modifiedKey = item["key"].toString() + " " + QString::number(i);
                    item["key"] = modifiedKey;
                    modifiedArray.append(item);
                }
                // Add to new QJsonObject with updated key names
                newObject.insert(key + " " + QString::number(i), modifiedArray);
            }
        }
    }
    propertyMap = mPropertyBrowser->createProperties(newObject);
}
