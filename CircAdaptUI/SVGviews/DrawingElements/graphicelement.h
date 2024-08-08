#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <QGraphicsPathItem>
#include <QBrush>
#include <QPen>
#include <QObject>

class GraphicElement : public QObject, public QGraphicsPathItem
{
    Q_OBJECT

public:
    GraphicElement(QGraphicsObject* parent);
    void setSelected(bool isSelected);

protected:
    QPen m_penDefault;
    QPen m_penSelected;
    QBrush m_Brush;
    bool m_isSelected;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // GRAPHICELEMENT_H
