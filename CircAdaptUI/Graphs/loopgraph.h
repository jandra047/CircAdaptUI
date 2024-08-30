#ifndef LOOPGRAPH_H
#define LOOPGRAPH_H
#include "CircAdaptUI/graphcontainer.h"
#include "CircAdaptUI/Signals/loopsignal.h"

class LoopGraph : public GraphContainer<LoopSignal>
{
public:
    LoopGraph(QWidget* parent);

    QString getPoint(const QPoint& pos) override;
    void addSignal(LoopSignal* signal) override;
    void displaySnapshot(Buffer& buffer) override;
    void showSignal(QAction* signal) override;
    void displayReference(Buffer& buffer);

private:
    QVector<LoopSignal*> m_Snapshots;
    QVector<LoopSignal*> m_References;
    void addSnapshotSignal(LoopSignal* signal);
    void addReferenceSignal(LoopSignal* signal);
};

#endif // LOOPGRAPH_H
