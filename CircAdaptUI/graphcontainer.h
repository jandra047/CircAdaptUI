#ifndef GRAPHCONTAINER_H
#define GRAPHCONTAINER_H
#include "qcustomplot.h"
#include "buffer.h"

template<typename SignalType>
class GraphContainer : public QCustomPlot
{
public:
    using ptr_type = SignalType*;
    GraphContainer(QWidget* parent = Q_NULLPTR);
    ~GraphContainer();
    void updateGraph(Buffer& buffer);
    void addSignal(ptr_type);
private:
    void zoom(QWheelEvent*);
    QVector<ptr_type> m_Signals;
};

#endif // GRAPHCONTAINER_H
