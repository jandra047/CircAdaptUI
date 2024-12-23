#ifndef MODELGRAPHICSVIEW_H
#define MODELGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsSvgItem>
#include "viewtypes.h"

#include "CircAdaptUI/SVGviews/svgtorsoobject.h"
#include "CircAdaptUI/SVGviews/svgheartobject.h"
#include "CircAdaptUI/SVGviews/svgtissueobject.h"

class Buffer;

class ModelGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    using ViewType = vt::ViewType;

    ModelGraphicsView(PropertyBrowserBase* propertyBrowser, QWidget *parent = nullptr);
    ~ModelGraphicsView();
    void showView(ViewType viewType);
    ToggleButtonGroup* getSubMenu(ViewType viewType);

protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    QGraphicsScene *scene;
    SVGTorsoObject *torsoSvg;
    SVGHeartObject *heartSvg;
    SVGTissueObject *tissueSvg;

    void updateView(SVGObjectBase* item);

public: signals:
    void showProperties(QList<QtBrowserItem*> browserItems);
public slots:
    void showOxygen(bool isVisible);
    void updateOxygen(Buffer& buffer);

};


#endif // MODELGRAPHICSVIEW_H
