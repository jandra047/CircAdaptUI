#ifndef SHUNTELEMENT_H
#define SHUNTELEMENT_H

#include "graphicelement.h"

class ShuntElement : public GraphicElement
{
public:
    ShuntElement(QString name, const QPointF& point, SVGObjectBase* parent = Q_NULLPTR);
    QPainterPath mPath;
    bool parsePathDataFast( QStringView dataStr, QPainterPath & path );
private:
    QString arrow = "m 89.268212,88.598815 4.508266,-4.50826 v 2.25413 h 9.312852 v -2.25413 l 4.50826,4.50826 -4.50826,4.50827 v -2.25414 h -9.312852 v 2.25414 z";
};

#endif // SHUNTELEMENT_H
