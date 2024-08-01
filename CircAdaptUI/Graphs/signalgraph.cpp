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
    QCPGraphDataContainer::const_iterator it;
    for (auto signal : m_Signals)
    {
        if (signal->visible())
        {
            it = signal->data()->constEnd();
            QVariant details;
            if (signal->selectTest(pos, false, &details)) // QPoint could be e.g. event->pos() of a mouse event
            {
                QCPDataSelection dataPoints = details.value<QCPDataSelection>();
                if (dataPoints.dataPointCount() > 0)
                    it = signal->data()->at(dataPoints.dataRange().begin());
            }
            string += QString("<span style=\"color: %1\"><b>%2:</b></span> %3 %4<br>")
                          .arg(signal->getColor().name())
                          .arg(signal->getDisplayName())
                          .arg((*it).value, 0, 'f', 2)
                          .arg(signal->getUnit());
        }
    }
    string = QString("<b>Time:</b> %1<hr>").arg((*it).key, 0, 'f', 2) + string;
    return string;
}
