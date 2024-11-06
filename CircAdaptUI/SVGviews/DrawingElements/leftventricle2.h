#ifndef LEFTVENTRICLE2_H
#define LEFTVENTRICLE2_H

#include "CircAdaptUI/SVGviews/drawingelementgroup.h"
#include "graphicelement.h"

class LeftVentricle2 : public DrawingElementGroup
{
public:
    LeftVentricle2(SVGObjectBase* parent);
    void setSelected(bool isSelected);
    bool m_isSelected = false;
    const QString name()  { return m_name; }

private:
    QMap<QString, QString> namePath;
    SVGObjectBase* m_SVGObject;
    QString m_name = "Left ventricular wall";
};

#endif // LEFTVENTRICLE2_H
