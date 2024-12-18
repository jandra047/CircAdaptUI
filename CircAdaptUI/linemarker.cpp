#include "linemarker.h"
#include "Graphs/mmode.h"

LineMarker::LineMarker(SignalGraph* parent) :
    QCPItemStraightLine(parent)
{
    if (MMode* derived = dynamic_cast<MMode*>(parent))
        setPen(QPen(Qt::white, 2));
    else
        setPen(QPen(Qt::black, 2));
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
