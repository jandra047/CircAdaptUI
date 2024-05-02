#include "graphcontainer.h"

GraphContainer::GraphContainer(QWidget* parent) :
    QCustomPlot(parent)
{
    currentLayer()->setMode(QCPLayer::lmBuffered);
    setInteractions(QCP::iRangeZoom);
    axisRect()->setRangeZoom(Qt::Horizontal);
    xAxis->ticker()->setTickCount(5);
    xAxis->grid()->setPen(QPen(QColor(0xd0d0d0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    yAxis->ticker()->setTickCount(5);
    yAxis->grid()->setPen(QPen(QColor(0xd0d0d0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBackground(QColor(0xededed));
    yAxis->setRange(-1,1);
    xAxis->setRange(0,8);
}

void GraphContainer::createSignals(int const N_signals)
{
    mSignals.reserve(N_signals);
    for (int i = 0; i < N_signals; i++)
    {
        Signal* signal = new Signal(this->xAxis, this->yAxis);
        signal->setLayer(this->currentLayer());
        mSignals.push_back(signal);
    }
}

void GraphContainer::updateGraph()
{
    for (int i = 0; i < mSignals.size(); i++)
    {
        mSignals[i]->updateGraph();
    }
    currentLayer()->replot();
}
