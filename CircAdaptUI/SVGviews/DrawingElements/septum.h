#ifndef SEPTUM_H
#define SEPTUM_H

#include "CircAdaptUI/SVGviews/drawingelementgroup.h"

class Septum : public DrawingElementGroup
{
public:
    Septum(SVGObjectBase* parent);
    void setSelected(bool isSelected);
    bool m_isSelected = false;
    const QString name()  { return m_name; }
    static QList<std::pair<QString, QString>> namePath;
    static QList<QString> patchNames;

private:
    SVGObjectBase* m_SVGObject;
    QString m_name = "Septal wall";

};

#endif // SEPTUM_H
