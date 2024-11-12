#include "rightventricle.h"

QMap<QString, QString> RightVentricle::namePath
{
    {"RV basal anterior" , QString("m 66.234,225.781 c 6.987,-9.437 17.178,-17.604 30.182,-23.377 12.946,-5.747 27.165,-8.45 41.219,-8.407 0,0 0.026,-0.155 0.026,-0.155 0,0 -0.081,-31.149 -0.081,-31.149 0,0 -0.04,-0.104 -0.04,-0.104 -20.99,-0.053 -42.224,3.992 -61.558,12.575 -19.309,8.571 -34.471,20.671 -44.913,34.655 0,0 0.204,0.104 0.204,0.104 0,0 34.772,15.762 34.772,15.762 0,0 0.189,0.096 0.189,0.096" )},
    {"RV basal lateral" , QString("m 66.617,289.333 c -7.179,-9.351 -11.334,-20.211 -11.391,-31.761 -0.057,-11.498 3.953,-22.335 10.98,-31.699 0,0 -0.162,-0.094 -0.162,-0.094 0,0 -35.188,-15.412 -35.188,-15.412 0,0 -0.137,-0.025 -0.137,-0.025 -10.481,13.991 -16.461,30.178 -16.376,47.35 0.085,17.149 6.209,33.282 16.803,47.198 0,0 0.218,-0.085 0.218,-0.085 0,0 35.051,-15.393 35.051,-15.393 0,0 0.202,-0.079 0.202,-0.079")},
    {"RV basal posterior" , QString("m 66.226,288.815 c 6.984,9.438 17.173,17.606 30.176,23.381 12.944,5.749 27.162,8.455 41.217,8.414 0,0 0.025,0.154 0.025,0.154 0,0 -0.089,31.15 -0.089,31.15 0,0 -0.04,0.104 -0.04,0.104 -20.991,0.049 -42.223,-3.998 -61.555,-12.584 -19.306,-8.575 -34.465,-20.677 -44.904,-34.663 0,0 0.204,-0.103 0.204,-0.103 0,0 34.777,-15.758 34.777,-15.758 0,0 0.189,-0.095 0.189,-0.095")},
    {"RV mid anterior" , QString("m 137.799,194.031 c 0,0 -0.098,29.91 -0.098,29.91 0,0 0.013,0.34 0.013,0.34 -7.341,-0.026 -14.77,1.385 -21.532,4.387 -6.827,3.031 -12.169,7.326 -15.815,12.289 0,0 -0.023,0.036 -0.023,0.036 0,0 -33.797,-15.493 -33.797,-15.493 0,0 0.041,-0.149 0.041,-0.149 6.976,-9.264 17.06,-17.278 29.876,-22.968 12.997,-5.77 27.277,-8.472 41.386,-8.407 0,0 -0.051,0.055 -0.051,0.055")},
    {"RV mid lateral" , QString("m 66.325,225.781 c 0,0 33.701,14.916 33.701,14.916 0,0 0.39,0.161 0.39,0.161 -3.674,4.889 -5.771,10.55 -5.741,16.556 0.03,6.064 2.224,11.763 6.014,16.663 0,0 0.029,0.032 0.029,0.032 0,0 -34.262,14.876 -34.262,14.876 0,0 -0.149,-0.101 -0.149,-0.101 -6.989,-9.259 -11.025,-19.971 -11.081,-31.355 -0.057,-11.543 3.984,-22.42 11.063,-31.809 0,0 0.036,0.061 0.036,0.061")},
    {"RV mid posterior" , QString("m 137.782,320.576 c 0,0 -0.09,-29.911 -0.09,-29.911 0,0 0.013,-0.34 0.013,-0.34 -7.341,0.025 -14.769,-1.386 -21.53,-4.389 -6.827,-3.032 -12.167,-7.329 -15.813,-12.292 0,0 -0.022,-0.036 -0.022,-0.036 0,0 -33.801,15.487 -33.801,15.487 0,0 0.04,0.15 0.04,0.15 6.974,9.265 17.056,17.281 29.871,22.972 12.995,5.772 27.275,8.476 41.383,8.414 0,0 -0.051,-0.055 -0.051,-0.055")},
    {"RV apical" , QString("m 138.222,224.276 c 0,0 -0.786,33.097 -0.786,33.097 0,0 0.347,33.101 0.347,33.101 -0.396,0.002 -0.737,0.001 -1.133,-0.005 -23.599,-0.331 -42.667,-15.546 -42.236,-33.701 0.431,-18.155 20.209,-32.824 43.808,-32.492")}
};

RightVentricle::RightVentricle(SVGObjectBase* parent) :
    DrawingElementGroup(parent),
    m_SVGObject(parent)
{

    for (auto [name, path] : namePath.asKeyValueRange())
    {
        GraphicElement* element = new GraphicElement(name, parent);
        QPainterPath p;
        GraphicElement::parsePathDataFast(path, p);

        element->setBrush(QBrush(QColor(215, 238, 244)));
        QPen pen = element->penDefault();
        pen.setWidth(3);
        element->setPenDefault(pen);
        element->setPath(p);
        addToGroup(element);
    }
    setZValue(1);

}

void RightVentricle::setSelected(bool isSelected)
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
