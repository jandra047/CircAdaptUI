#ifndef SVGOBJECTBASE_H
#define SVGOBJECTBASE_H

#include <QGraphicsObject>
#include <QGraphicsSvgItem>
#include <QPushButton>
#include "CircAdaptUI/PropertyBrowser/propertybrowserbase.h"
#include "togglebuttongroup.h"
#include <QObject>

class SVGObjectBase : public QGraphicsObject
{
    Q_OBJECT

public:
    SVGObjectBase(const QString& bgImg,
                  PropertyBrowserBase* propertyBrowser,
                  const QString& elementId = "",
                  QGraphicsItem* parent = Q_NULLPTR);
    ~SVGObjectBase() {};
    /**
     * @brief Returns the required bounding rectangle for this graph item
     * @details This group item does not show anything and is only used to group dynamic
     * graph elements. This function is only present because it is required and delives
     * a vaid dummy rectangle
     * @return A dummy rectangle
     */
    virtual QRectF boundingRect( void ) const override;


    /**
     * @brief Paint function
     * @details This group item does not show anything and is only used to group dynamic
     * graph elements, so this function does not paint anything and is only present because
     * it is required.
     */
    virtual void paint( QPainter *, const QStyleOptionGraphicsItem *, QWidget * ) override;

    ToggleButtonGroup* getSubMenuContainer() { return subMenuContainer; }

    QtProperty* mProperties;
    PropertyBrowserBase* mPropertyBrowser;
    QMap<QString, QList<QtBrowserItem*>> propertyMap;

    void setVisibleProperties(QList<QtBrowserItem*> visibleProperties)
    {
        m_VisibleProperties = visibleProperties;
        mPropertyBrowser->showProperties(m_VisibleProperties);
    };

    QList<QtBrowserItem*>& getVisibleProperties() { return m_VisibleProperties; }


protected:
    QGraphicsSvgItem m_bgItem;
    ToggleButtonGroup* subMenuContainer;
    QList<QtBrowserItem*> m_VisibleProperties;

public slots:
    virtual void handleSubMenuSwitch(QAbstractButton* button) {};
};

#endif // SVGOBJECTBASE_H
