#ifndef LINEMARKER_H
#define LINEMARKER_H

#include "qcustomplot.h"

class LineMarker : public QCPItemStraightLine
{
    Q_OBJECT
public:
    LineMarker(QCustomPlot* parent);
signals:
    void xPosChanged(double x);
public slots:
    void setXPos(double x);
};

#endif // LINEMARKER_H
