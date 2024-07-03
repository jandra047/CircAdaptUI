#include "loopgraph.h"

LoopGraph::LoopGraph(QWidget* parent) :
    GraphContainer<LoopSignal>(parent)
{
    xAxis->setLabel("Volume [mL]");
    xAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->setLabel("Pressure [mmHg]");
    yAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    xAxis->setRange(0, 200);
    yAxis->setRange(0, 200);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    xAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
}
