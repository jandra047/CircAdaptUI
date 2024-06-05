#include "graphcontainer.h"
#include <loopsignal.h>
#include <timesignal.h>

template<typename SignalType>
GraphContainer<SignalType>::GraphContainer(QWidget* parent) :
    QCustomPlot(parent)
{
    setOpenGl(true);
    currentLayer()->setMode(QCPLayer::lmBuffered);
    setInteraction(QCP::iRangeDrag);
    xAxis->ticker()->setTickCount(5);
    xAxis->setTickLabelFont(QFont("Times", 12, QFont::Bold));
    xAxis->grid()->setPen(QPen(QColor(0xd0d0d0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    yAxis->ticker()->setTickCount(5);
    yAxis->setTickLabelFont(QFont("Times", 12, QFont::Bold));
    yAxis->grid()->setPen(QPen(QColor(0xaaaaaa), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setBackground(QColor(0xededed));
    setBackground(QColor(0xaaaaaa));
    yAxis->setRange(0,20000);
    xAxis->setRange(0,3);

    connect(this, &QCustomPlot::mouseWheel, this, &GraphContainer::zoom);
}

template<typename SignalType>
GraphContainer<SignalType>::~GraphContainer()
{
    while (mSignals.count())
    {
        delete mSignals.takeLast();
    }

}

template<typename SignalType>
void GraphContainer<SignalType>::addSignal(SignalType* signal)
{
    signal->setLayer(this->currentLayer());
    mSignals.push_back(signal);
}

template<typename SignalType>
void GraphContainer<SignalType>::zoom(QWheelEvent* event)
{
    // Calculate the zoom factor based on the wheel angle delta
    double zoomFactor = 1 - event->angleDelta().y() / 1200.0; // Adjust as needed

    if (event->modifiers() & Qt::ShiftModifier)
    {
        xAxis->setRangeUpper(xAxis->range().upper * zoomFactor);
    }
    else
    {
        yAxis->setRangeUpper(yAxis->range().upper * zoomFactor);
    }

    replot();

    // Accept the event to prevent further processing
    event->accept();
}

template<typename SignalType>
void GraphContainer<SignalType>::updateGraph(Buffer& buffer)
{
    for (int i = 0; i < mSignals.size(); i++)
    {
        mSignals[i]->updateGraph(buffer);
    }
    currentLayer()->replot();
}

template class GraphContainer<LoopSignal>;
template class GraphContainer<TimeSignal>;
