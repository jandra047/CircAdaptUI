#include "septum.h"

Septum::Septum(SVGObjectBase* parent):
    GraphicElement("Septal wall", parent)
{
    QPainterPath m_path1;
    QPainterPath m_path2;
    QPainterPath m_path3;
    QPainterPath m_path4;
    QPainterPath m_path5;
    GraphicElement::parsePathDataFast(PATCH_SV_BASAL_ANTERIOR_PATH, m_path1);
    GraphicElement::parsePathDataFast(PATCH_SV_BASAL_POSTERIOR_PATH, m_path2);
    GraphicElement::parsePathDataFast(PATCH_SV_MID_ANTERIOR_PATH, m_path3);
    GraphicElement::parsePathDataFast(PATCH_SV_MID_POSTERIOR_PATH, m_path4);
    GraphicElement::parsePathDataFast(PATCH_SV_APICAL_PATH, m_path5);

    m_path.addPath(m_path1);
    m_path.addPath(m_path2);
    m_path.addPath(m_path3);
    m_path.addPath(m_path4);
    m_path.addPath(m_path5);

    m_penDefault.setWidth(3);
    setPen(m_penDefault);
    setPath(m_path);
    setBrush(QBrush(QColor(255, 246, 240)));
}
