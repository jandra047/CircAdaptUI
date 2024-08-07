#include "modelgraphicsview.h"
#include <QGraphicsProxyWidget>


ModelGraphicsView::ModelGraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this)),
    torsoSvg(new SVGTorsoObject()),
    heartSvg(new SVGHeartObject()),
    tissueSvg(new SVGTissueObject())
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

void ModelGraphicsView::updateView(SVGObjectBase *item)
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

QWidget* ModelGraphicsView::getSubMenu(ViewType viewType)
{
    switch (viewType) {
    case ViewType::Torso:
        return torsoSvg->getSubMenuContainer();
    case ViewType::Heart:
        return heartSvg->getSubMenuContainer();
    case ViewType::Tissue:
        return tissueSvg->getSubMenuContainer();
    }

}
