#include "modelgraphicsview.h"
#include <QGraphicsProxyWidget>


ModelGraphicsView::ModelGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this)),
    torsoSvg(new QGraphicsSvgItem(":/CircAdapt/svgs/Full_Body.svg")),
    heartSvg(new QGraphicsSvgItem(":/CircAdapt/svgs/Heart.svg")),
    tissueSvg(new QGraphicsSvgItem(":/CircAdapt/svgs/Heart_segments.svg"))
{
    setScene(scene);

    // Add items to scene
    scene->addItem(torsoSvg);
    scene->addItem(heartSvg);
    scene->addItem(tissueSvg);

    // Initially, only show torso
    heartSvg->setVisible(false);
    tissueSvg->setVisible(false);

    scene->setSceneRect(scene->itemsBoundingRect());
}

ModelGraphicsView::~ModelGraphicsView()
{
    delete scene;
    delete torsoSvg;
    delete heartSvg;
    delete tissueSvg;
}

void ModelGraphicsView::showView(ViewType viewType)
{
    switch (viewType) {
    case ViewType::Torso:
        updateView(torsoSvg);
        break;
    case ViewType::Heart:
        updateView(heartSvg);
        break;
    case ViewType::Tissue:
        updateView(tissueSvg);
        break;
    }
}

void ModelGraphicsView::updateView(QGraphicsItem *item)
{
    torsoSvg->setVisible(item == torsoSvg);
    heartSvg->setVisible(item == heartSvg);
    tissueSvg->setVisible(item == tissueSvg);
    scene->setSceneRect(item->boundingRect());
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void ModelGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
