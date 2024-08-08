#ifndef SVGTORSOOBJECT_H
#define SVGTORSOOBJECT_H

#include "svgobjectbase.h"

class SVGTorsoObject : public SVGObjectBase
{
public:
    SVGTorsoObject(QGraphicsItem* parent = Q_NULLPTR) ;
    void handleSubMenuSwitch(QAbstractButton* button) override;

private:
    void showSystemic();
    void showPulmonary();
    void createCovers();
    QGraphicsRectItem* coverSystemic;
    QGraphicsRectItem* coverPulmonary;
};

#endif // SVGTORSOOBJECT_H
