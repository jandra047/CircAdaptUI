#ifndef SVGTISSUEOBJECT_H
#define SVGTISSUEOBJECT_H

#include "svgobjectbase.h"
#include "DrawingElements/rightatrium.h"
#include "DrawingElements/leftatrium.h"
#include "DrawingElements/rightventricle.h"
#include "DrawingElements/septum.h"
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
    RightVentricle* rightVentricle;
    Septum* septum;
    LeftVentricle2* leftVentricle;
    QGraphicsRectItem* m_CoverElement;
    void showView(const ViewType& viewType);


    void handleSubMenuSwitch(QAbstractButton* button) override;
};

#endif // SVGTISSUEOBJECT_H
