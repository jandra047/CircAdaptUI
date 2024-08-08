#ifndef SVGOBJECTBASE_H
#define SVGOBJECTBASE_H

#include <QGraphicsObject>
#include <QGraphicsSvgItem>
#include <QPushButton>
#include "togglebuttongroup.h"

class SVGObjectBase : public QGraphicsObject
{
    Q_OBJECT

public:
    SVGObjectBase(const QString& bgImg, QGraphicsItem* parent = Q_NULLPTR);
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

protected:
    QGraphicsSvgItem m_bgItem;
    ToggleButtonGroup* subMenuContainer;

public slots:
    virtual void handleSubMenuSwitch(QAbstractButton* button) {};
};

#endif // SVGOBJECTBASE_H
