#include "leftatrium.h"

LeftAtrium::LeftAtrium(SVGObjectBase* parent):
    GraphicElement("Left atrial wall", parent),
    m_pathString("m 159.216,140.558 c 21.35,-13.338 27.944,-41.887 14.606,-63.236 -3.851,-6.165 -8.426,-10.742 -14.589,-14.596 0,0 18.36,-17.057 18.36,-17.057 11.048,14.529 35.596,23.562 64.031,23.562 0,0 -0.149,0 -0.149,0 28.435,0 52.984,-9.033 64.031,-23.562 0,0 18.36,17.057 18.36,17.057 -6.163,3.854 -10.738,8.431 -14.589,14.596 -13.338,21.349 -6.744,49.898 14.606,63.236 0,0 -17.131,18.501 -17.131,18.501 -10.159,-15.431 -35.652,-25.32 -65.277,-25.32 0,0 0.149,0 0.149,0 -29.624,0 -55.118,9.889 -65.276,25.32 0,0 -17.132,-18.501 -17.132,-18.501")
{
    GraphicElement::parsePathDataFast(m_pathString, m_path);
    m_path.translate(45.0, 0);

    m_penDefault.setWidth(3);
    setPen(m_penDefault);
    m_penSelected.setWidth(5);
    QBrush brush(QColor(255, 200, 200));
    setPath(m_path);
    setBrush(brush);
}
