#ifndef MMODE_H
#define MMODE_H

#include "CircAdaptUI/Graphs/signalgraph.h"

class MMode : public SignalGraph
{
public:
    MMode(QWidget* parent, QString xLabel = "", QString yLabel = "");
    ~MMode() = default;

    QString getPoint(const QPoint& pos) override { return QString(""); };

};

#endif // MMODE_H
