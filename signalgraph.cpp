#include "signalgraph.h"


SignalGraph::SignalGraph(QWidget* parent) :
    GraphContainer(parent)
{
    xAxis->setLabel("Time [s]");
    xAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->setLabel("Pressure [mmHg]");
    yAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    xAxis->setRangeUpper(1.5);
}
