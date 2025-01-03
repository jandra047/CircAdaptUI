#ifndef LOOPGRAPH_H
#define LOOPGRAPH_H
#include "CircAdaptUI/Widgets/graphgrid.h"
#include "CircAdaptUI/graphcontainer.h"
#include "CircAdaptUI/Signals/loopsignal.h"

class LoopGraph : public GraphContainer<LoopSignal>
{
    Q_OBJECT
public:
    LoopGraph(QWidget* parent);

    QString getPoint(const QPoint& pos) override;
    void addSignal(LoopSignal* signal) override;
    void displaySnapshot(Buffer& buffer) override;
    void showSignal(QAction* signal) override;
    void displayReference(Buffer& buffer);
    void setup(const QJsonObject& jsonObject);

private:
    QVector<LoopSignal*> m_References;
    QVector<LoopSignal*> m_Snapshots;
    void addSnapshotSignal(LoopSignal* signal);
    void addReferenceSignal(LoopSignal* signal);
    int findClosestPointBySortKey(LoopSignal* signal, double targetSortKey);

    QString xVarName;
    QString xUnit;
    QString yVarName;
    QString yUnit;

    double m_snapshotMarkerPos;
    double m_referenceMarkerPos;

    std::pair<QString, QString> parseLabel(const QString& label);

public slots:
    void updateMarker(GraphGrid::ColType colType, double x);
    void clearSnapshot();
    void clearReference();
    void clearCurrent();
    void clearAllGraphs();
    void rescaleAxes();

};

#endif // LOOPGRAPH_H
