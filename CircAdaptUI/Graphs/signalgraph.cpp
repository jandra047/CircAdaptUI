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
