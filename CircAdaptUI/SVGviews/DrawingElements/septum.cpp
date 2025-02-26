#include "septum.h"

QList<QString> Septum::patchNames;

QList<std::pair<QString, QString>> Septum::namePath
{
    {"SV basal anterior" , QString("m 222.036,257.172 c -0.025,-10.876 2.725,-21.875 8.547,-31.87 5.796,-9.951 13.957,-17.743 23.375,-23.086 0,0 -0.06,-0.144 -0.06,-0.144 0,0 -15.554,-27.041 -15.554,-27.041 0,0 -0.078,-0.075 -0.078,-0.075 -14.061,7.989 -26.245,19.633 -34.9,34.493 -8.644,14.841 -12.761,31.161 -12.784,47.312 0,0 0.188,0.012 0.188,0.012 0,0 31.092,0.388 31.092,0.388 0,0 0.174,0.011 0.174,0.011")},
    {"SV basal posterior" , QString("m 253.916,312.259 c -9.453,-5.379 -17.635,-13.227 -23.42,-23.243 -5.76,-9.971 -8.472,-20.925 -8.433,-31.753 0,0 -0.155,-0.019 -0.155,-0.019 0,0 -31.195,0.075 -31.195,0.075 0,0 -0.104,0.03 -0.104,0.03 -0.046,16.172 4.011,32.529 12.612,47.421 8.591,14.872 20.713,26.548 34.721,34.588 0,0 0.103,-0.158 0.103,-0.158 0,0 15.776,-26.795 15.776,-26.795 0,0 0.095,-0.146 0.095,-0.146")},
    {"SV mid anterior" , QString("m 254.084,202.183 c 0,0 14.819,26.033 14.819,26.033 0,0 0.177,0.29 0.177,0.29 -4.921,2.788 -9.186,6.857 -12.213,12.055 -3.056,5.248 -4.49,11.025 -4.459,16.735 0,0 0.004,0.04 0.004,0.04 0,0 -30.306,-0.528 -30.306,-0.528 0,0 -0.047,-0.145 -0.047,-0.145 0.054,-10.722 2.808,-21.547 8.546,-31.398 5.818,-9.99 14.021,-17.805 23.486,-23.149 0,0 -0.007,0.067 -0.007,0.067")},
    {"SV mid posterior" , QString("m 222.097,257.137 c 0,0 29.955,0.063 29.955,0.063 0,0 0.34,-0.01 0.34,-0.01 -0.024,5.656 1.391,11.379 4.4,16.587 3.037,5.259 7.341,9.372 12.312,12.18 0,0 0.036,0.017 0.036,0.017 0,0 -15.505,26.044 -15.505,26.044 0,0 -0.149,-0.031 -0.149,-0.031 -9.281,-5.371 -17.31,-13.137 -23.012,-23.008 -5.782,-10.011 -8.492,-21.012 -8.432,-31.881 0,0 0.055,0.039 0.055,0.039")},
    {"SV apical" , QString("m 262.056,280.747 c 0,0 23.508,-23.374 23.508,-23.374 0,0 -23.47,-23.414 -23.47,-23.414 -12.81,12.841 -12.827,33.926 -0.038,46.788")}
};

Septum::Septum(SVGObjectBase* parent) :
    DrawingElementGroup(parent),
    m_SVGObject(parent)
{

    for (const auto pair : namePath)
    {
        patchNames.append(pair.first);
        QString name = pair.first;
        QString path = pair.second;
        GraphicElement* element = new GraphicElement(name, parent);
        QPainterPath p;
        GraphicElement::parsePathDataFast(path, p);

        element->setBrush(QBrush(QColor(255, 246, 240)));
        QPen pen = element->penDefault();
        pen.setWidth(3);
        element->setPenDefault(pen);
        element->setPath(p);
        addToGroup(element);
    }
    setZValue(1);

}

void Septum::setSelected(bool isSelected)
{
    if (isSelected) {
        setZValue(10);
        selectAll();
        setSelectable(true);
        m_SVGObject->setVisibleProperties(m_SVGObject->propertyMap[name()]);
    }
    else
    {
        clearSelection();
        setSelectable(false);
        setZValue(1);
    }

}
