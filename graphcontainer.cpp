#include "graphcontainer.h"

namespace {
    int sign(double x) {
        return (x > 0) ? 1 : -1;
    }
}

GraphContainer::GraphContainer(QWidget* parent) :
    QCustomPlot(parent)
{
    currentLayer()->setMode(QCPLayer::lmBuffered);
    xAxis->ticker()->setTickCount(5);
    xAxis->grid()->setPen(QPen(QColor(0xd0d0d0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    yAxis->ticker()->setTickCount(5);
    yAxis->grid()->setPen(QPen(QColor(0xd0d0d0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBackground(QColor(0xededed));
    yAxis->setRange(0,200);
    xAxis->setRange(0,3);

    connect(this, &QCustomPlot::mouseWheel, this, &GraphContainer::zoom);
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

void GraphContainer::zoom(QWheelEvent* event)
{
    // Calculate the zoom factor based on the wheel angle delta
    double zoomFactor = 1 - event->angleDelta().y() / 1200.0; // Adjust as needed

    if (event->modifiers() & Qt::ShiftModifier)
    {
        xAxis->setRange(0, xAxis->range().upper * zoomFactor);
    }
    else if (event->modifiers() & Qt::ControlModifier)
    {
        // TODO: Make dependent on current ranges
        yAxis->setRangeLower(yAxis->range().lower - 15 * zoomFactor * sign(event->angleDelta().y()));
    }
    else
    {
        yAxis->setRangeUpper(yAxis->range().upper * zoomFactor);
    }

    replot();

    // Accept the event to prevent further processing
    event->accept();

}
