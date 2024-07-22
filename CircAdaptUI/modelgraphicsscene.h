#ifndef MODELGRAPHICSSCENE_H
#define MODELGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

class ModelGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ModelGraphicsScene(QObject* parent);
    QGraphicsSvgItem* mBackGroundItem;
    QGraphicsObject* obj;

};

#endif // MODELGRAPHICSSCENE_H
