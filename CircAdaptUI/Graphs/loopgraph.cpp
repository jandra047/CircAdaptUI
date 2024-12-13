#include "loopgraph.h"
#include "CircAdaptUI/loopmarker.h"

LoopGraph::LoopGraph(QWidget* parent) :
    GraphContainer<LoopSignal>(parent),
    m_referenceMarkerPos(-1),
    m_snapshotMarkerPos(-1)
{
    xAxis->setLabel("Volume [mL]");
    yAxis->setLabel("Pressure [mmHg]");
    xAxis->setRange(0, 200);
    yAxis->setRange(0, 200);
    yAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    xAxis->grid()->setZeroLinePen(QPen(QColor(0,0,0), 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    addLayer("snapshot", currentLayer(), QCustomPlot::limBelow);
    addLayer("reference", layer("snapshot"), QCustomPlot::limBelow);
    addLayer("markers");
}

QString LoopGraph::getPoint(const QPoint& pos)
{
    QString string = QString("<b>%1:</b> %2 %3 <br><b>%4:</b> %5 %6")
                         .arg(xVarName)
                         .arg(xAxis->pixelToCoord(pos.x()), 0, 'f', 1)
                         .arg(xUnit)
                         .arg(yVarName)
                         .arg(yAxis->pixelToCoord(pos.y()), 0, 'f', 1)
                         .arg(yUnit);
    return string;
}

void LoopGraph::addSignal(LoopSignal* signal)
{
    GraphContainer<LoopSignal>::addSignal(signal);

    addSnapshotSignal(signal);
    addReferenceSignal(signal);
}

void LoopGraph::addSnapshotSignal(LoopSignal* signal)
{
    LoopSignal* snapshotSignal = new LoopSignal(*signal);
    QPen pen = snapshotSignal->pen();
    QColor color = pen.color();
    color.setAlphaF(0.5);

    pen.setColor(color);
    pen.setStyle(Qt::DashLine);
    snapshotSignal->setPen(pen);
    snapshotSignal->setLayer("snapshot");
    m_Snapshots.push_back(snapshotSignal);
}

void LoopGraph::addReferenceSignal(LoopSignal* signal)
{
    LoopSignal* referenceSignal = new LoopSignal(*signal);
    QPen pen = referenceSignal->pen();
    QColor color = pen.color();
    color.setAlphaF(0.5);

    int currentSaturation = color.saturation();
    int reducedSaturation = currentSaturation * 0.4;
    color.setHsv(color.hue(), reducedSaturation, color.value(), color.alpha());

    pen.setColor(color);
    pen.setStyle(Qt::DotLine);
    referenceSignal->setPen(pen);

    referenceSignal->setLayer("reference");
    m_References.push_back(referenceSignal);
}

void LoopGraph::displaySnapshot(Buffer& buffer)
{
    for (int i = 0; i < m_Snapshots.size(); i++)
    {
        LoopSignal* signal = m_Snapshots.at(i);
        if (!signal->getMarker())
        {
            signal->createMarker();
        }
        QVector<double> yData = buffer.getSnapshot(signal->getYVar());
        QVector<double> xData = buffer.getSnapshot(signal->getXVar());
        QVector<double> tData = buffer.getSnapshot("t");
        signal->setData(tData, xData, yData);
    }
    updateMarker(GraphGrid::ColType::SNAPSHOT, m_snapshotMarkerPos);
    layer("snapshot")->replot();
}

void LoopGraph::displayReference(Buffer& buffer)
{
    for (int i = 0; i < m_References.size(); i++)
    {
        LoopSignal* signal = m_References.at(i);
        if (!signal->getMarker())
        {
            signal->createMarker();
        }
        QVector<double> yData = buffer.getSnapshot(signal->getYVar());
        QVector<double> xData = buffer.getSnapshot(signal->getXVar());
        QVector<double> tData = buffer.getSnapshot("t");
        signal->setData(tData, xData, yData);
    }
    layer("reference")->replot();
}

void LoopGraph::showSignal(QAction* action)
{
    GraphContainer<LoopSignal>::showSignal(action);
    m_Snapshots.at(action->data().toInt())->setVisible(action->isChecked());
    layer("snapshot")->replot();
    m_References.at(action->data().toInt())->setVisible(action->isChecked());
    layer("reference")->replot();
}

void LoopGraph::updateMarker(GraphGrid::ColType colType, double x)
{
    if (colType == GraphGrid::ColType::REFERENCE)
    {
        m_referenceMarkerPos = x;
        for (auto signal : m_References)
        {
            if (signal->visible())
            {
                int i = findClosestPointBySortKey(signal, x);
                double xpos = signal->data()->at(i)->mainKey();
                double ypos = signal->data()->at(i)->mainValue();
                signal->getMarker()->setVisible(true);
                signal->getMarker()->setPosition(xpos,ypos);
            }
        }
    }
    if (colType == GraphGrid::ColType::SNAPSHOT)
    {
        m_snapshotMarkerPos = x;
        if (!m_Snapshots.at(0)->data()->isEmpty())
        {
            for (auto signal : m_Snapshots)
            {
                if (signal->visible())
                {
                    int i = findClosestPointBySortKey(signal, x);
                    double xpos = signal->data()->at(i)->mainKey();
                    double ypos = signal->data()->at(i)->mainValue();
                    signal->getMarker()->setVisible(true);
                    signal->getMarker()->setPosition(xpos,ypos);
                }
            }
        }
    }

    layer("markers")->replot();
}

int LoopGraph::findClosestPointBySortKey(LoopSignal* signal, double targetSortKey) {
    if (!signal || signal->data()->isEmpty()) {
        return -1;  // Invalid curve or no data
    }

    // Access the data container of the curve
    const QCPDataContainer<QCPCurveData>& dataContainer = *(signal->data());

    // Use a lambda for binary search to find the closest point
    auto lower = std::lower_bound(dataContainer.constBegin(), dataContainer.constEnd(), targetSortKey,
                                  [](const QCPCurveData &data, double key) {
                                      return data.sortKey() < key;
                                  });

    if (lower == dataContainer.constBegin()) {
        // The closest point is the first one
        return 0;
    } else if (lower == dataContainer.constEnd()) {
        // The closest point is the last one
        return dataContainer.size() - 1;
    }

    // Check the two points around the lower bound to find the closest one
    auto prev = std::prev(lower);
    if (std::abs(prev->sortKey() - targetSortKey) < std::abs(lower->sortKey() - targetSortKey)) {
        return std::distance(dataContainer.constBegin(), prev);
    } else {
        return std::distance(dataContainer.constBegin(), lower);
    }
}

void LoopGraph::setup(const QJsonObject& jsonObject)
{
    QJsonArray signalArray = jsonObject["Signals"].toArray();

    for (auto item : signalArray)
    {
        QJsonObject itemObject = item.toObject();
        LoopSignal* signal = new LoopSignal(
            xAxis,
            yAxis,
            itemObject["displayName"].toString(),
            itemObject["yVar"].toString(),
            itemObject["xVar"].toString(),
            QColor(itemObject["color"].toString()),
            itemObject["isVisible"].toBool());

        addSignal(signal);
    }

    QString title = jsonObject["title"].toString();
    setTitle(title, QFont("Liberation Sans", 12, QFont::Bold));

    QString xLabel = jsonObject["xLabel"].toString();
    auto xLabelPair = parseLabel(xLabel);
    xVarName = xLabelPair.first;
    xUnit = xLabelPair.second;
    xAxis->setLabel(xLabel);

    QString yLabel = jsonObject["yLabel"].toString();
    auto yLabelPair = parseLabel(yLabel);
    yVarName = yLabelPair.first;
    yUnit = yLabelPair.second;
    yAxis->setLabel(yLabel);

    auto menu = buildMenu(this);
    setContextMenu(menu);
    QObject::connect(menu.second, &QActionGroup::triggered, this, [=](QAction* action) { showSignal(action); });

}

std::pair<QString, QString> LoopGraph::parseLabel(const QString& label)
{
    QString varName{};
    QString unit{};

    QRegularExpressionMatch match = QRegularExpression("\\[(.*)\\]").match(label);

    if (match.hasMatch())
    {
        unit = match.captured(1);
    }

    varName = label.split(" ")[0];

    return std::pair<QString, QString> {varName, unit};
}

void LoopGraph::clearSnapshot()
{
    for (auto item : m_Snapshots)
    {
        item->clear();
    }
    layer("snapshot")->replot();
    layer("markers")->replot();
}

void LoopGraph::clearReference()
{
    for (auto item : m_References)
    {
        item->clear();
    }
    layer("reference")->replot();
    layer("markers")->replot();
}

void LoopGraph::clearCurrent()
{
    for (auto item : m_Signals)
    {
        item->clear();
    }
    currentLayer()->replot();
}

void LoopGraph::clearAllGraphs()
{
    clearCurrent();
    clearReference();
    clearSnapshot();
}
