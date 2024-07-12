#ifndef SIGNALGRAPH_H
#define SIGNALGRAPH_H
#include "CircAdaptUI/graphcontainer.h"
#include "CircAdaptUI/Signals/timesignal.h"

class SignalGraph : public GraphContainer<TimeSignal>
{
public:
    SignalGraph(QWidget* parent, QString xLabel = "", QString yLabel = "");

    QString getPoint(const QPoint& pos) override;

};

#endif // SIGNALGRAPH_H
