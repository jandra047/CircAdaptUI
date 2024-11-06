#include "drawingelementgroup.h"
#include "DrawingElements/textcircle.h"


bool DrawingElementGroup::sceneEventFilter(QGraphicsItem* watched, QEvent* event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress && childrenSelectable()) {
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

void DrawingElementGroup::selectAll()
{
    for (QGraphicsItem* item : childItems()) {
        GraphicElement* element = qgraphicsitem_cast<GraphicElement*>(item);
        if (element) {
            element->setSelected(true);
        }
    }
}

void DrawingElementGroup::setVisible(bool isVisible)
{
    QGraphicsItemGroup::setVisible(isVisible);

    if (childrenSelectable() && isVisible)
    {
        if (m_selectedItem)
        {
            m_selectedItem->SVGObject()->setVisibleProperties(m_selectedItem->SVGObject()->propertyMap[m_selectedItem->name()]);
        }
        else if (!childItems().isEmpty())
        {
            auto* firstChild = qgraphicsitem_cast<GraphicElement*>(childItems().at(0));
            if (firstChild)
            {
                firstChild->SVGObject()->setVisibleProperties(QList<QtBrowserItem*> {});
            }
        }
    }

}

void DrawingElementGroup::updateText(Buffer& buffer)
{
    for (auto item : childItems())
    {
        auto s = dynamic_cast<TextCircle*>(item);
        if (s)
        {
            s->update(buffer);
        }
    }
}
