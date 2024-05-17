#ifndef GRAPHCONTAINER_H
#define GRAPHCONTAINER_H
#include <qcustomplot.h>

template<typename SignalType>
class GraphContainer : public QCustomPlot
{
public:
    using ptr_type = SignalType*;
    GraphContainer(QWidget* parent = Q_NULLPTR);
    void updateGraph();
    void createSignals(int, QVector<QString>);
    QVector<ptr_type> mSignals;
private:
    void zoom(QWheelEvent*);
};

#endif // GRAPHCONTAINER_H
