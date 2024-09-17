#include "drawingelementgroup.h"


bool DrawingElementGroup::sceneEventFilter(QGraphicsItem* watched, QEvent* event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress) {
        QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            clearSelection();
            return selectElement(watched);
        }
    }
    return QGraphicsItemGroup::sceneEventFilter(watched, event);
}

bool DrawingElementGroup::selectElement(QGraphicsItem* item)
{
    GraphicElement* element = qgraphicsitem_cast<GraphicElement*>(item);
    if (element)
    {
        element->setSelected(true);
        m_selectedItem = element;
        element->SVGObject()->setVisibleProperties(element->SVGObject()->propertyMap[element->name()]);
        return true;
    }
    else
        return false;

}

void DrawingElementGroup::clearSelection()
{
    for (QGraphicsItem* item : childItems()) {
        GraphicElement* element = qgraphicsitem_cast<GraphicElement*>(item);
        if (element) {
            element->setSelected(false);
        }
    }
}

void DrawingElementGroup::setVisible(bool isVisible)
{
    QGraphicsItemGroup::setVisible(isVisible);
    if (m_selectedItem && isVisible)
        m_selectedItem->SVGObject()->setVisibleProperties(m_selectedItem->SVGObject()->propertyMap[m_selectedItem->name()]);
    if (isVisible && !m_selectedItem)
        qgraphicsitem_cast<GraphicElement*> (childItems().at(0))->SVGObject()->setVisibleProperties(QList<QtBrowserItem*> {});
}
