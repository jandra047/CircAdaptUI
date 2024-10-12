#include "mmode.h"

MMode::MMode(QWidget* parent, QString xLabel, QString yLabel):
    SignalGraph(parent, "Time [s]", "Distance [mm]")
{
    axisRect()->setBackground(QColor(Qt::black));
    yAxis->grid()->setVisible(false);
    xAxis->grid()->setVisible(false);
    // yAxis->setTicks(false);
    // yAxis->setTickLabels(false);
    // yAxis->setLabel("");

    TimeSignal* sigLvEndo = new TimeSignal
    (
        xAxis,
        yAxis,
        "LvEndo",
        "LvEndo",
        "t",
        QColor(Qt::white),
        true,
        "no unit"
    );
    addSignal(sigLvEndo);

    TimeSignal* sigLvEpi = new TimeSignal
    (
        xAxis,
        yAxis,
        "LvEpi",
        "LvEpi",
        "t",
        QColor(Qt::white),
        true,
        "no unit"
    );
    addSignal(sigLvEpi);
    sigLvEpi->setBrush(QBrush(Qt::white));
    sigLvEpi->setChannelFillGraph(sigLvEndo);

    TimeSignal* sigRvEpi = new TimeSignal
    (
        xAxis,
        yAxis,
        "RvEpi",
        "RvEpi",
        "t",
        QColor(Qt::white),
        true,
        "no unit"
    );
    addSignal(sigRvEpi);

    TimeSignal* sigRvEndo = new TimeSignal
    (
        xAxis,
        yAxis,
        "RvEndo",
        "RvEndo",
        "t",
        QColor(Qt::white),
        true,
        "no unit"
    );
    addSignal(sigRvEndo);
    sigRvEpi->setBrush(QBrush(Qt::white));
    sigRvEpi->setChannelFillGraph(sigRvEndo);


    TimeSignal* sigSvEpi = new TimeSignal
    (
        xAxis,
        yAxis,
        "SvEpi",
        "SvEpi",
        "t",
        QColor(Qt::white),
        true,
        "no unit"
    );
    addSignal(sigSvEpi);


    TimeSignal* sigSvEndo = new TimeSignal
    (
        xAxis,
        yAxis,
        "SvEndo",
        "SvEndo",
        "t",
        QColor(Qt::white),
        true,
        "no unit"
    );
    addSignal(sigSvEndo);
    sigSvEpi->setBrush(QBrush(Qt::white));
    sigSvEpi->setChannelFillGraph(sigSvEndo);
}

void MMode::zoom(QWheelEvent* event)
{
    // Calculate the zoom factor based on the wheel angle delta
    double zoomFactor = 1 - event->angleDelta().y() / 1200.0; // Adjust as needed

    if (event->modifiers() && Qt::ShiftModifier)
    {
        double max_X = getMaxX();
        if (xAxis->range().upper * zoomFactor > max_X && !m_zoomPastX && !isEmpty())
            xAxis->setRangeUpper(max_X);
        else
            xAxis->setRangeUpper(xAxis->range().upper * zoomFactor);
    }
    else
    {
        yAxis->setRangeUpper(0);
        yAxis->setRangeLower(yAxis->range().lower * zoomFactor);
    }

    replot();

    // Accept the event to prevent further processing
    event->accept();
}
