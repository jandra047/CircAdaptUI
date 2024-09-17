#ifndef DRAWINGELEMENTGROUP_H
#define DRAWINGELEMENTGROUP_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneEvent>
#include "DrawingElements/graphicelement.h"

class DrawingElementGroup : public QGraphicsItemGroup
{
public:
    DrawingElementGroup(QGraphicsItem* parent):
        QGraphicsItemGroup(parent),
        m_selectedItem(Q_NULLPTR)
    {
        setFiltersChildEvents(true);
    };

    bool sceneEventFilter(QGraphicsItem* watched, QEvent* event) override;
    bool selectElement(QGraphicsItem* item);
    void clearSelection();
    void setVisible(bool isVisible);

private:
    GraphicElement* m_selectedItem;
};

#endif // DRAWINGELEMENTGROUP_H
