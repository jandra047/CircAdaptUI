#include "rightventricle.h"

RightVentricle::RightVentricle(SVGObjectBase* parent):
    GraphicElement("Right ventricular wall", parent)
{
    QPainterPath m_path1;
    QPainterPath m_path2;
    QPainterPath m_path3;
    QPainterPath m_path4;
    QPainterPath m_path5;
    QPainterPath m_path6;
    QPainterPath m_path7;
    GraphicElement::parsePathDataFast(PATCH_RV_BASAL_ANTERIOR_PATH, m_path1);
    GraphicElement::parsePathDataFast(PATCH_RV_BASAL_LATERAL_PATH, m_path2);
    GraphicElement::parsePathDataFast(PATCH_RV_BASAL_POSTERIOR_PATH, m_path3);
    GraphicElement::parsePathDataFast(PATCH_RV_MID_ANTERIOR_PATH, m_path4);
    GraphicElement::parsePathDataFast(PATCH_RV_MID_LATERAL_PATH, m_path5);
    GraphicElement::parsePathDataFast(PATCH_RV_MID_POSTERIOR_PATH, m_path6);
    GraphicElement::parsePathDataFast(PATCH_RV_APICAL_PATH, m_path7);

    m_path.addPath(m_path1);
    m_path.addPath(m_path2);
    m_path.addPath(m_path3);
    m_path.addPath(m_path4);
    m_path.addPath(m_path5);
    m_path.addPath(m_path6);
    m_path.addPath(m_path7);
    // m_path.translate(45.0, 0);
    m_penDefault.setWidth(3);
    setPen(m_penDefault);
    setPath(m_path);

    setBrush(QBrush(QColor(215, 238, 244)));

}
