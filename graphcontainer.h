#ifndef GRAPHCONTAINER_H
#define GRAPHCONTAINER_H
#include <qcustomplot.h>
#include <signal.h>

class GraphContainer : public QCustomPlot
{
public:
    GraphContainer(QWidget* parent);
    QList<Signal* > mSignals;
    void updateGraph();
    void createSignals(int);
};

#endif // GRAPHCONTAINER_H
