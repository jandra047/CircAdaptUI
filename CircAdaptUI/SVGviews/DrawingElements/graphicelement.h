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

protected:
    QPen m_Pen;
    QBrush m_Brush;
};

#endif // GRAPHICELEMENT_H
