#ifndef LOOPMARKER_H
#define LOOPMARKER_H

#include "qcustomplot.h"

class LoopMarker : public QCPItemEllipse
{
public:
    LoopMarker(QCustomPlot* parent):
        QCPItemEllipse(parent)
    {

    }

    LoopMarker(const LoopMarker& other):
        QCPItemEllipse(other.parentPlot())
    {
        setPen(other.pen());
        setBrush(other.brush());
        setVisible(false);
    }
};

#endif // LOOPMARKER_H
