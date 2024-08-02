#ifndef SIGNALGRAPH_H
#define SIGNALGRAPH_H
#include "CircAdaptUI/graphcontainer.h"
#include "CircAdaptUI/Signals/timesignal.h"

class SignalGraph : public GraphContainer<TimeSignal>
{
public:
    SignalGraph(QWidget* parent, QString xLabel = "", QString yLabel = "");

    QString getPoint(const QPoint& pos) override;

    void drawVerticalLine(const QPoint& pos);
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void onMouseMove(QMouseEvent* event);
    void onMouseRelease(QMouseEvent* event);
};

#endif // SIGNALGRAPH_H
