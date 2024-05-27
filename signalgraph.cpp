#include "signalgraph.h"


SignalGraph::SignalGraph(QWidget* parent) :
    GraphContainer<TimeSignal>(parent)
{
    xAxis->setLabel("Time [s]");
    xAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->setLabel("Pressure [mmHg]");
    yAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    xAxis->setRangeUpper(1.5);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setRangeDrag(Qt::Vertical);
}
