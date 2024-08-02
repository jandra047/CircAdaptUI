#include "linemarker.h"

LineMarker::LineMarker(QCustomPlot* parent) :
    QCPItemStraightLine(parent)
{
    setPen(QPen(QColor("black"), 2));
    setVisible(false);
}

void LineMarker::setXPos(double x)
{
    setVisible(true);
    point1->setCoords(x, 0);
    point2->setCoords(x, 1);
    m_xPos = x;
    layer()->replot();
}
