#include "signalgraph.h"


SignalGraph::SignalGraph(QWidget* parent, QString xLabel, QString yLabel) :
    GraphContainer<TimeSignal>(parent),
    m_lineMarker(Q_NULLPTR)
{
    xAxis->setLabel(xLabel);
    yAxis->setLabel(yLabel);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setRangeDrag(Qt::Vertical);
    connect(this, &QCustomPlot::mouseMove, this, &SignalGraph::onMouseMove);
    connect(this, &QCustomPlot::mouseRelease, this, &SignalGraph::onMouseRelease);

    addLayer("lineMarker");
    lineMarkerLayer = layer("lineMarker");
    lineMarkerLayer->setMode(QCPLayer::lmBuffered);
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

    m_lineMarker->setXPos(key);
    emit m_lineMarker->xPosChanged(key);
}

void SignalGraph::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_lineMarker)
        {
            double xCoord = xAxis->pixelToCoord(event->pos().x());
            m_dragStartX = xCoord;
            if (qAbs(xCoord - m_lineMarker->xPos()) < m_verticalLineDistanceTreshold) // Threshold to detect click near the line
            {
                m_lineMarker->setDragging(true);
            }
            else
            {
                GraphContainer<TimeSignal>::mousePressEvent(event);
            }
        }
        else
        {
            GraphContainer<TimeSignal>::mousePressEvent(event);
        }
    }
}

void SignalGraph::onMouseMove(QMouseEvent* event)
{
    if (m_lineMarker)
    {
        double xCoord = xAxis->pixelToCoord(event->pos().x());
        if (m_lineMarker->getDragging())
        {
            drawVerticalLine(event->pos());
        }
        else
        {
            if (qAbs(xCoord - m_lineMarker->xPos()) < m_verticalLineDistanceTreshold) // Threshold to detect hover near the line
            {
                setCursor(Qt::SizeHorCursor);
            }
            else
            {
                unsetCursor();
            }
        }
    }
}

void SignalGraph::onMouseRelease(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_lineMarker)
        {
            double xCoord = xAxis->pixelToCoord(event->pos().x());
            m_lineMarker->setDragging(false);
            if (qAbs(xCoord - m_dragStartX) < 1e-5)
            {
                // TODO: hide lines and markers when line is clicked
                drawVerticalLine(event->pos());
            }
            else
            {
            }
        }
    }
}

void SignalGraph::displaySnapshot(Buffer& buffer)
{
    for (int i = 0; i < m_Signals.size(); i++)
    {
        TimeSignal* signal = m_Signals.at(i);
        QVector<double> yData = buffer.getSnapshot(signal->getYVar());
        QVector<double> tData = buffer.getSnapshot(signal->getXVar());
        signal->setData(tData, yData);
    }
    replot();
}

void SignalGraph::showSignal(QAction* action)
{
    GraphContainer<TimeSignal>::showSignal(action);
    emit autoscaleNeeded();
}
