#ifndef SIGNALGRAPH_H
#define SIGNALGRAPH_H
#include <graphcontainer.h>
#include <timesignal.h>

class SignalGraph : public GraphContainer<TimeSignal>
{
public:
    SignalGraph(QWidget* parent);
};

#endif // SIGNALGRAPH_H
