#include "signalgraph.h"


SignalGraph::SignalGraph(QWidget* parent, QString xLabel, QString yLabel) :
    GraphContainer<TimeSignal>(parent)
{
    xAxis->setLabel(xLabel);
    yAxis->setLabel(yLabel);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setRangeDrag(Qt::Vertical);
    connect(this, &QCustomPlot::mouseMove, this, &SignalGraph::onMouseMove);
    connect(this, &QCustomPlot::mouseRelease, this, &SignalGraph::onMouseRelease);
}

QString SignalGraph::getPoint(const QPoint& pos)
{
    QString string{};
    double xCoord = pos.x();

    double key = xAxis->pixelToCoord(xCoord);

    for (auto signal : m_Signals)
    {
        if (signal->visible())
        {
            // Find the closest data point to the key (x-coordinate)
            QCPGraphDataContainer::const_iterator it = signal->data()->findBegin(key, true);

            if (it != signal->data()->constEnd())
            {
                string += QString("<span style=\"color: %1\"><b>%2:</b></span> %3 %4<br>")
                              .arg(signal->getColor().name())
                              .arg(signal->getDisplayName())
                              .arg((*it).value, 0, 'f', 1)
                              .arg(signal->getUnit());
            }
        }
    }

    string = QString("<b>Time:</b> %1 s<hr>").arg(key, 0, 'f', 2) + string;
    return string;
}

void SignalGraph::drawVerticalLine(const QPoint& pos)
{
    // Convert the pixel x-coordinate to the plot's x-coordinate
    double key = xAxis->pixelToCoord(pos.x());

    // Set the position of the line
    m_lineMarker.point1->setCoords(key, 0); // Bottom point (x, y) in plot coordinates
    m_lineMarker.point2->setCoords(key, 1); // Top point (x, y) in plot coordinates

    m_lineMarker.setVisible(true);
    m_lineMarker.setXPos(key);
    emit m_lineMarker.xPosChanged(key);
    // Update the plot to show the new line
    currentLayer()->replot();
}

void SignalGraph::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        double xCoord = xAxis->pixelToCoord(event->pos().x());
        if (qAbs(xCoord - m_lineMarker.xPos()) < 0.1) // Threshold to detect click near the line
        {
            // m_dragging = true;
            m_lineMarker.setDragging(true);
            // m_dragStartX = xCoord;
        }
    }
}

void SignalGraph::onMouseMove(QMouseEvent* event)
{
    double xCoord = xAxis->pixelToCoord(event->pos().x());
    if (m_lineMarker.getDragging())
    {
        // m_lineMarker.setXPos(xCoord);
        drawVerticalLine(event->pos());
    }
    else
    {
        if (qAbs(xCoord - m_lineMarker.xPos()) < 0.1) // Threshold to detect hover near the line
        {
            setCursor(Qt::SizeHorCursor);
        }
        else
        {
            unsetCursor();
        }
    }
}

void SignalGraph::onMouseRelease(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lineMarker.setDragging(false);
        drawVerticalLine(event->pos());
    }
}
