#include "rightatrium.h"

RightAtrium::RightAtrium(SVGObjectBase* parent):
    GraphicElement("Right atrial wall", parent),
    m_pathString("m -14.807,163.44 c 0,-8.7 -3.889,-16.268 -11.968,-23.288 0,0 -0.016,0.018 -0.016,0.018 -11.705,-10.316 -17.693,-23.111 -17.693,-37.799 0,0 0,-0.014 0,-0.014 0,-14.689 5.988,-27.483 17.693,-37.8 0,0 0.016,0.018 0.016,0.018 8.079,-7.019 11.968,-14.588 11.968,-23.288 0,0 26.707,-0.006 26.707,-0.006 0,10.248 10.56,19.003 26.12,21.656 0,0 -0.017,-0.027 -0.017,-0.027 23.121,3.759 40.151,14.562 46.125,29.261 8.789,21.626 -11.956,44.027 -45.952,49.619 0,0 0.024,0.001 0.024,0.001 -15.56,2.653 -26.121,11.407 -26.121,21.656 0,0 -26.886,-0.007 -26.886,-0.007")
{

    GraphicElement::parsePathDataFast(m_pathString, m_path);
    m_path.translate(45.0, 0);

    m_penDefault.setWidth(3);
    setPen(m_penDefault);

    m_penSelected.setWidth(5);

    setBrush(QColor(215, 238, 244));

    setPath(m_path);
}
