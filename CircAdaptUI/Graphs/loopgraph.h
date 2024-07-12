#ifndef LOOPGRAPH_H
#define LOOPGRAPH_H
#include "CircAdaptUI/graphcontainer.h"
#include "CircAdaptUI/Signals/loopsignal.h"

class LoopGraph : public GraphContainer<LoopSignal>
{
public:
    LoopGraph(QWidget* parent);

    QString getPoint(const QPoint& pos) override { return QString(); };
};

#endif // LOOPGRAPH_H
