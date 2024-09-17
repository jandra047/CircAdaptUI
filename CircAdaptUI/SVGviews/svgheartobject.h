#ifndef SVGHEARTOBJECT_H
#define SVGHEARTOBJECT_H

#include "svgobjectbase.h"
#include "drawingelementgroup.h"

class SVGHeartObject : public SVGObjectBase
{
public:
    enum class ViewType
    {
        Valves,
        Shunts,
        Pericardium
    };

    SVGHeartObject(PropertyBrowserBase* propertyBrowser, QGraphicsItem* parent = Q_NULLPTR);

    DrawingElementGroup* valveGroup;
    DrawingElementGroup* shuntGroup;

    void handleSubMenuSwitch(QAbstractButton* button) override;
    void showValves();
    void showShunts();
    void showPericardium();
    void afterSetup();

};

#endif // SVGHEARTOBJECT_H
