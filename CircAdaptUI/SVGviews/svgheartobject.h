#ifndef SVGHEARTOBJECT_H
#define SVGHEARTOBJECT_H

#include "svgobjectbase.h"

class SVGHeartObject : public SVGObjectBase
{
public:
    enum class ViewType
    {
        Valves,
        Shunts,
        Pericardium
    };

    SVGHeartObject(QGraphicsItem* parent = Q_NULLPTR);

    QGraphicsItemGroup* valveGroup;
    QGraphicsItemGroup* shuntGroup;

    void handleSubMenuSwitch(QAbstractButton* button) override;
    void showValves();
    void showShunts();
    void showPericardium();

};

#endif // SVGHEARTOBJECT_H
