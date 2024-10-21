#include "modelgraphicsview.h"


ModelGraphicsView::ModelGraphicsView(PropertyBrowserBase* propertyBrowser, QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this)),
    torsoSvg(new SVGTorsoObject(propertyBrowser)),
    heartSvg(new SVGHeartObject(propertyBrowser)),
    tissueSvg(new SVGTissueObject(propertyBrowser))
{
    setScene(scene);

    // Add items to scene
    scene->addItem(torsoSvg);
    scene->addItem(heartSvg);
    scene->addItem(tissueSvg);

    showView(ViewType::Torso);

    setRenderHint(QPainter::Antialiasing, true);
    scene->setSceneRect(scene->itemsBoundingRect());
}

ModelGraphicsView::~ModelGraphicsView()
{
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

    item->mPropertyBrowser->showProperties(item->getVisibleProperties());
}

void ModelGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

ToggleButtonGroup* ModelGraphicsView::getSubMenu(ViewType viewType)
{
    switch (viewType) {
    case ViewType::Torso:
        return torsoSvg->getSubMenuContainer();
    case ViewType::Heart:
        return heartSvg->getSubMenuContainer();
    case ViewType::Tissue:
        return tissueSvg->getSubMenuContainer();
    default:
        return torsoSvg->getSubMenuContainer();
    }

}

void ModelGraphicsView::showOxygen(bool isVisible)
{
    heartSvg->showOxygen(isVisible);
}

void ModelGraphicsView::updateOxygen(Buffer& buffer)
{
    heartSvg->updateOxygen(buffer);
}
