#include "loopgraph.h"

LoopGraph::LoopGraph(QWidget* parent) :
    GraphContainer<LoopSignal>(parent)
{
    xAxis->setLabel("Volume [mL]");
    yAxis->setLabel("Pressure [mmHg]");
    xAxis->setRange(0, 200);
    yAxis->setRange(0, 200);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    xAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
}

QString LoopGraph::getPoint(const QPoint& pos)
{
    QString string = QString("<b>%1:</b> %2 mL <br><b>%3:</b> %4 mmHg")
                         .arg("Volume")
                         .arg(xAxis->pixelToCoord(pos.x()), 0, 'f', 1)
                         .arg("Pressure")
                         .arg(yAxis->pixelToCoord(pos.y()), 0, 'f', 1);
    return string;
}
