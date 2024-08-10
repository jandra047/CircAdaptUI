#include "leftventricle.h"

LeftVentricle::LeftVentricle(QGraphicsObject* parent):
    GraphicElement(parent)
{
    QPainterPath m_path1;
    QPainterPath m_path2;
    QPainterPath m_path3;
    QPainterPath m_path4;
    QPainterPath m_path5;
    QPainterPath m_path6;
    QPainterPath m_path7;
    QPainterPath m_path8;
    QPainterPath m_path9;
    QPainterPath m_path10;
    QPainterPath m_path11;
    GraphicElement::parsePathDataFast(PATCH_LV_BASAL_ANTERIOR_PATH, m_path1);
    GraphicElement::parsePathDataFast(PATCH_LV_BASAL_POSTERIOR_PATH, m_path2);
    GraphicElement::parsePathDataFast(PATCH_LV_BASAL_POSTERIOR_LATERAL_PATH, m_path3);
    GraphicElement::parsePathDataFast(PATCH_LV_BASAL_ANTERIOR_LATERAL_PATH, m_path4);
    GraphicElement::parsePathDataFast(PATCH_LV_MID_ANTERIOR_PATH, m_path5);
    GraphicElement::parsePathDataFast(PATCH_LV_MID_POSTERIOR_PATH, m_path6);
    GraphicElement::parsePathDataFast(PATCH_LV_MID_ANTERIOR_LATERAL_PATH, m_path7);
    GraphicElement::parsePathDataFast(PATCH_LV_MID_POSTERIOR_LATERAL_PATH, m_path8);
    GraphicElement::parsePathDataFast(PATCH_LV_APICAL_ANTERIOR_PATH, m_path9);
    GraphicElement::parsePathDataFast(PATCH_LV_APICAL_POSTERIOR_PATH, m_path10);
    GraphicElement::parsePathDataFast(PATCH_LV_APICAL_LATERAL_PATH, m_path11);

    m_path.addPath(m_path1);
    m_path.addPath(m_path2);
    m_path.addPath(m_path3);
    m_path.addPath(m_path4);
    m_path.addPath(m_path5);
    m_path.addPath(m_path6);
    m_path.addPath(m_path7);
    m_path.addPath(m_path8);
    m_path.addPath(m_path9);
    m_path.addPath(m_path10);
    m_path.addPath(m_path11);

    m_penDefault.setWidth(3);
    setPen(m_penDefault);
    setPath(m_path);

    setBrush(QBrush(QColor(255, 200, 200)));
}
