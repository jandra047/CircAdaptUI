#ifndef TEXTCIRCLE_H
#define TEXTCIRCLE_H

#include "CircAdaptUI/SVGviews/svgobjectbase.h"
#include <QGraphicsTextItem>
#include "CircAdaptUI/buffer.h"

class TextCircle : public QGraphicsTextItem
{
public:
    TextCircle(QString name, QPointF center, SVGObjectBase* parent);
    ~TextCircle() = default;
    void setText(const QString& text);
    void update(Buffer& buffer);
private:
    void updateCircleBounds();
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget ) override;
    QRectF boundingRect() const override;

    const QString m_name;
    QPointF m_Center;
    QRectF m_CircleBounds;
    Qt::Alignment m_Alignment;


};
#endif // TEXTCIRCLE_H
