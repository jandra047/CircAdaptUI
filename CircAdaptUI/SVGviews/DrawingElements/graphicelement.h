#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <QGraphicsPathItem>
#include <QBrush>
#include <QPen>
#include <QObject>

class GraphicElement : public QGraphicsPathItem
{

public:
    GraphicElement(QGraphicsObject* parent);
    void setSelected(bool isSelected);


protected:
    QPen m_penDefault;
    QPen m_penSelected;
    QBrush m_Brush;
    bool m_isSelected;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    static bool parsePathDataFast( QStringView dataStr, QPainterPath & path );
};

#endif // GRAPHICELEMENT_H
