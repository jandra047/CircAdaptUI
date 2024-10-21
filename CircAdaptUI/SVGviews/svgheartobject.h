#ifndef SVGHEARTOBJECT_H
#define SVGHEARTOBJECT_H

#include "svgobjectbase.h"
#include "drawingelementgroup.h"

class Buffer;

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
    DrawingElementGroup* oxygenGroup;

    void handleSubMenuSwitch(QAbstractButton* button) override;
    void showValves();
    void showShunts();
    void showPericardium();

    void showOxygen(bool isVisible);

public slots:
    void updateOxygen(Buffer& buffer);

};

#endif // SVGHEARTOBJECT_H
