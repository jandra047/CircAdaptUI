#ifndef SVGTISSUEOBJECT_H
#define SVGTISSUEOBJECT_H

#include "svgobjectbase.h"
#include "DrawingElements/rightatrium.h"
#include "DrawingElements/leftatrium.h"
#include "DrawingElements/rightventricle2.h"
#include "DrawingElements/septum2.h"
#include "DrawingElements/leftventricle2.h"
#include "drawingelementgroup.h"

class SVGTissueObject : public SVGObjectBase
{
public:

    enum class ViewType
    {
        Ra,
        La,
        Rv,
        Sv,
        Lv
    };


    SVGTissueObject(PropertyBrowserBase* propertyBrowser, QGraphicsItem* parent = Q_NULLPTR);

    void createCovers();
    RightAtrium* rightAtrium;
    LeftAtrium* leftAtrium;
    RightVentricle2* rightVentricle;
    Septum2* septum;
    LeftVentricle2* leftVentricle;
    QGraphicsRectItem* m_CoverElement;
    void showView(const ViewType& viewType);
    void createProperties();


    void handleSubMenuSwitch(QAbstractButton* button) override;
};

#endif // SVGTISSUEOBJECT_H
