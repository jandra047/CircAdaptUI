#include "signalgraph.h"


SignalGraph::SignalGraph(QWidget* parent, QString xLabel, QString yLabel) :
    GraphContainer<TimeSignal>(parent)
{
    xAxis->setLabel(xLabel);
    xAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->setLabel(yLabel);
    yAxis->setLabelFont(QFont("Mononoki", 14, QFont::Bold));
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setRangeDrag(Qt::Vertical);
}
