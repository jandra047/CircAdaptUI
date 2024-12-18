#ifndef LINEMARKER_H
#define LINEMARKER_H

#include "qcustomplot.h"

class SignalGraph;

class LineMarker : public QCPItemStraightLine
{
    Q_OBJECT
public:
    LineMarker(SignalGraph* parent);

    const double& xPos() { return m_xPos; };
    void setDragging(bool isDragging) { m_Dragging = isDragging; };
    const bool& getDragging() { return m_Dragging; }
private:
    double m_xPos{0};
    bool m_Dragging = false;
signals:
    void xPosChanged(double x);
public slots:
    void setXPos(double x);
};

#endif // LINEMARKER_H
