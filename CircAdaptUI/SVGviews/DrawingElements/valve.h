#ifndef VALVE_H
#define VALVE_H

#include "graphicelement.h"

class Valve : public GraphicElement
{
public:
    Valve(QPointF center, QGraphicsObject* parent = Q_NULLPTR);

    QPointF mCenter;
    QPainterPath mPath;

};

#endif // VALVE_H
