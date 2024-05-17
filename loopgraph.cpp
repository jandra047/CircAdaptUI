#include "loopgraph.h"

LoopGraph::LoopGraph(QWidget* parent) :
    GraphContainer<LoopSignal>(parent)
{
    xAxis->setLabel("Volume [mL]");
    xAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->setLabel("Pressure [mmHg]");
    yAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
}
