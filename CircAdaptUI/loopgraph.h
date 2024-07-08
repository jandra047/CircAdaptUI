#ifndef LOOPGRAPH_H
#define LOOPGRAPH_H
#include "graphcontainer.h"
#include "loopsignal.h"

class LoopGraph : public GraphContainer<LoopSignal>
{
public:
    LoopGraph(QWidget* parent);

    QString getPoint(const QPoint& pos) override { return QString(); };
};

#endif // LOOPGRAPH_H
