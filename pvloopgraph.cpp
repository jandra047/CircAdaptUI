#include "pvloopgraph.h"

PVLoopGraph::PVLoopGraph(QWidget* parent) :
    GraphContainer(parent)
{
    xAxis->setLabel("Volume [mL]");
    xAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->setLabel("Pressure [mmHg]");
    yAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));

}

void PVLoopGraph::updateGraph()
{
}
