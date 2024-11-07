#ifndef RIGHTVENTRICLE2_H
#define RIGHTVENTRICLE2_H

#include "CircAdaptUI/SVGviews/drawingelementgroup.h"

class RightVentricle2 : public DrawingElementGroup
{
public:
    RightVentricle2(SVGObjectBase* parent);
    void setSelected(bool isSelected);
    bool m_isSelected = false;
    const QString name()  { return m_name; }
    const QList<QString> patchNames() { return namePath.keys(); }
    static QMap<QString, QString> namePath;

private:
    SVGObjectBase* m_SVGObject;
    QString m_name = "Right ventricular wall";

};

#endif // RIGHTVENTRICLE2_H
