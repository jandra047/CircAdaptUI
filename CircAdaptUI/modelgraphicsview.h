#ifndef MODELGRAPHICSVIEW_H
#define MODELGRAPHICSVIEW_H

#include <QGraphicsView>

class ModelGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    ModelGraphicsView(QWidget* parent = Q_NULLPTR);

private:
    QGraphicsScene* m_SVGViewScene;
};

#endif // MODELGRAPHICSVIEW_H
