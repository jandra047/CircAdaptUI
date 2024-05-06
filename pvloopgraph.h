#ifndef PVLOOPGRAPH_H
#define PVLOOPGRAPH_H
#include <graphcontainer.h>

class PVLoopGraph : public GraphContainer
{
public:
    PVLoopGraph(QWidget* parent);
    void updateGraph();

};

#endif // PVLOOPGRAPH_H
