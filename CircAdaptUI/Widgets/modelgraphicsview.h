#ifndef MODELGRAPHICSVIEW_H
#define MODELGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsSvgItem>
#include "viewtypes.h"

class ModelGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    ModelGraphicsView(QWidget *parent = nullptr);
    ~ModelGraphicsView();
    void showView(ViewType viewType);

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QGraphicsScene *scene;
    QGraphicsSvgItem *torsoSvg;
    QGraphicsSvgItem *heartSvg;
    QGraphicsSvgItem *tissueSvg;

    void updateView(QGraphicsItem* item);
};


#endif // MODELGRAPHICSVIEW_H
