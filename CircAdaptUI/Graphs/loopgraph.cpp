#include "loopgraph.h"

LoopGraph::LoopGraph(QWidget* parent) :
    GraphContainer<LoopSignal>(parent)
{
    xAxis->setLabel("Volume [mL]");
    yAxis->setLabel("Pressure [mmHg]");
    xAxis->setRange(0, 200);
    yAxis->setRange(0, 200);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    xAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    addLayer("snapshot", currentLayer(), QCustomPlot::limBelow);
    addLayer("reference", layer("snapshot"), QCustomPlot::limBelow);
}

QString LoopGraph::getPoint(const QPoint& pos)
{
    QString string = QString("<b>%1:</b> %2 mL <br><b>%3:</b> %4 mmHg")
                         .arg("Volume")
                         .arg(xAxis->pixelToCoord(pos.x()), 0, 'f', 1)
                         .arg("Pressure")
                         .arg(yAxis->pixelToCoord(pos.y()), 0, 'f', 1);
    return string;
}

void LoopGraph::addSignal(LoopSignal* signal)
{
    GraphContainer<LoopSignal>::addSignal(signal);

    addSnapshotSignal(signal);

}

void LoopGraph::addSnapshotSignal(LoopSignal* signal)
{
    // Implement deepcopy!!
    LoopSignal* snapshotSignal = new LoopSignal(*signal);
    QPen pen = snapshotSignal->pen();
    QColor color = pen.color();
    color.setAlphaF(0.5);

    int currentSaturation = color.saturation();
    int reducedSaturation = currentSaturation * 0.4;  // Reduce saturation by 20%
    color.setHsv(color.hue(), reducedSaturation, color.value(), color.alpha());

    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    snapshotSignal->setPen(pen);
    m_Snapshots.push_back(snapshotSignal);
}

void LoopGraph::displaySnapshot(Buffer& buffer)
{
    for (int i = 0; i < m_Snapshots.size(); i++)
    {
        LoopSignal* signal = m_Snapshots.at(i);
        QVector<double> yData = buffer.getLastBeat()->get(signal->getYVar());
        QVector<double> xData = buffer.getLastBeat()->get(signal->getXVar());
        signal->setData(xData, yData);
    }

    layer("snapshot")->replot();
}

void LoopGraph::showSignal(QAction* action)
{
    GraphContainer<LoopSignal>::showSignal(action);
    m_Snapshots[action->data().toInt()]->setVisible(action->isChecked());
    layer("snapshot")->replot();
}
