#ifndef SEPTUM2_H
#define SEPTUM2_H

#include "CircAdaptUI/SVGviews/drawingelementgroup.h"

class Septum2 : public DrawingElementGroup
{
public:
    Septum2(SVGObjectBase* parent);
    void setSelected(bool isSelected);
    bool m_isSelected = false;
    const QString name()  { return m_name; }
    const QList<QString> patchNames() { return namePath.keys(); }
    static QMap<QString, QString> namePath;

private:
    SVGObjectBase* m_SVGObject;
    QString m_name = "Septal wall";

};

#endif // SEPTUM2_H
