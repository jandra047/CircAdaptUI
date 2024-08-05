#ifndef MODELGRAPHICSSCENE_H
#define MODELGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include "CircAdaptUI/SVGviews/svgobjectbase.h"

class ModelGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ModelGraphicsScene(QObject* parent);
    QGraphicsSvgItem* mBackGroundItem;
    // QGraphicsObject* obj;
    SVGObjectBase* m_torsoView;


};

#endif // MODELGRAPHICSSCENE_H
