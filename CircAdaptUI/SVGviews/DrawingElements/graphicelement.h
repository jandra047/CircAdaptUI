#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <QGraphicsPathItem>
#include <QBrush>
#include <QPen>
#include <QObject>
#include "CircAdaptUI/SVGviews/svgobjectbase.h"

class GraphicElement : public QGraphicsPathItem
{

public:
    GraphicElement(QString name, SVGObjectBase* parent);
    void setSelected(bool isSelected);
    const QString& name() { return m_Name; }
    SVGObjectBase* SVGObject() { return m_SVGObject; }
    static bool parsePathDataFast( QStringView dataStr, QPainterPath & path );
    QPen penDefault() { return m_penDefault; }
    QPen penSelected() { return m_penSelected; }
    void setPenDefault(const QPen& pen) { m_penDefault = pen; }
    void setPenSelected(const QPen& pen) { m_penSelected = pen; }

private:
    SVGObjectBase* m_SVGObject;

protected:
    QPen m_penDefault;
    QPen m_penSelected;
    QBrush m_Brush;
    bool m_isSelected;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;


    QString m_Name;
};

#endif // GRAPHICELEMENT_H
