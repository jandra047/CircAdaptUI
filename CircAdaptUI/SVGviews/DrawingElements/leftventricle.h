#ifndef LEFTVENTRICLE_H
#define LEFTVENTRICLE_H

#include "CircAdaptUI/SVGviews/drawingelementgroup.h"

class LeftVentricle : public DrawingElementGroup
{
public:
    LeftVentricle(SVGObjectBase* parent);
    void setSelected(bool isSelected);
    bool m_isSelected = false;
    const QString name()  { return m_name; }
    const QList<QString> patchNames() { return namePath.keys(); }
    static QMap<QString, QString> namePath;

private:
    SVGObjectBase* m_SVGObject;
    QString m_name = "Left ventricular wall";

};

#endif // LEFTVENTRICLE_H
