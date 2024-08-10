#ifndef LEFTATRIUM_H
#define LEFTATRIUM_H

#include "graphicelement.h"

class LeftAtrium : public GraphicElement
{
public:
    LeftAtrium(QGraphicsObject* parent);

private:
    QString m_pathString;
    QPainterPath m_path;
};

#endif // LEFTATRIUM_H
