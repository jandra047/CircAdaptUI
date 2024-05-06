#ifndef PVLOOPGRAPH_H
#define PVLOOPGRAPH_H
#include <graphcontainer.h>
#include <loopsignal.h>

class PVLoopGraph : public GraphContainer<LoopSignal>
{
public:
    PVLoopGraph(QWidget* parent);
};

#endif // PVLOOPGRAPH_H
