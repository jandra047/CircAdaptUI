#ifndef RIGHTATRIUM_H
#define RIGHTATRIUM_H

#include <QGraphicsObject>
#include <QString>
#include "graphicelement.h"

class RightAtrium : public GraphicElement
{
public:
    RightAtrium(SVGObjectBase* parent);

private:
    QString m_pathString;

    QPainterPath m_path;

};

#endif // RIGHTATRIUM_H
