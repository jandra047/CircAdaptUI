#ifndef DRAWINGELEMENTGROUP_H
#define DRAWINGELEMENTGROUP_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneEvent>
#include "DrawingElements/graphicelement.h"

class Buffer;

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
    void selectAll();
    void setVisible(bool isVisible);
    bool childrenSelectable() { return m_childrenSelectable; }
    void setSelectable(bool isSelectable) { m_childrenSelectable = isSelectable; }

private:
    GraphicElement* m_selectedItem;
    bool m_childrenSelectable = true;

public slots:
    void updateText(Buffer& buffer);
};

#endif // DRAWINGELEMENTGROUP_H
