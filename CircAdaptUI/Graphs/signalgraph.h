#ifndef SIGNALGRAPH_H
#define SIGNALGRAPH_H
#include "CircAdaptUI/graphcontainer.h"
#include "CircAdaptUI/Signals/timesignal.h"
#include "CircAdaptUI/linemarker.h"

class SignalGraph : public GraphContainer<TimeSignal>
{
    Q_OBJECT
public:
    SignalGraph(QWidget* parent, QString xLabel = "", QString yLabel = "");
    ~SignalGraph() = default;

    QString getPoint(const QPoint& pos) override;

    void drawVerticalLine(const QPoint& pos);
    void mousePressEvent(QMouseEvent *event) override;
    void displaySnapshot(Buffer& buffer) override;
    LineMarker* getLineMarker() { return m_lineMarker; }
    void setLineMarker(LineMarker* lineMarker) { m_lineMarker = lineMarker; m_lineMarker->setLayer(lineMarkerLayer); }
    void showSignal(QAction* action) override;

signals:
    void autoscaleNeeded();

public slots:
    void onMouseMove(QMouseEvent* event);
    void onMouseRelease(QMouseEvent* event);

private:
    double m_verticalLineDistanceTreshold = 0.05;
    double m_dragStartX = 0;
    QCPLayer* lineMarkerLayer;
    LineMarker* m_lineMarker;
};

#endif // SIGNALGRAPH_H
