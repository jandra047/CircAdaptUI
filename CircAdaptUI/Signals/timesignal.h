#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H
#include "dependencies/qcustomplot.h"
#include "CircAdaptUI/buffer.h"
#include "signalinterface.h"

/*!
 * \brief Wraps a QCPGraph class which contains a time signal.
 */
class TimeSignal : public QCPGraph, public SignalInterface
{

public:
    /*!
     * \brief TimeSignal
     * \param xAxis X axis of a QCP object
     * \param yAxis Y axis of a QCP object
     * \param yVar	Name of variable from buffer to be plotted on y-axis
     * \param xVar 	Name of variable from buffer to be plotted on x-axis
     * \param color Line color
     */
    TimeSignal(QCPAxis* xAxis,
               QCPAxis* yAxis,
               QString displayName,
               QString yVar,
               QString xVar = "t",
               QColor color = QColor(0,0,0),
               bool isVisible = true,
               QString unit = "",
               bool isInMainMenu = true) :
        QCPGraph(xAxis, yAxis),
        SignalInterface(
              displayName,
              yVar,
              xVar,
              color,
              isVisible,
              unit,
              isInMainMenu)
    {
        setPen(QPen(color, 2));
        setVisible(isVisible);
        QObject::connect(parentPlot(), &QCustomPlot::beforeReplot, this, [this]() { newLines.clear(); });
    };
    ~TimeSignal() {};
    /*!
     * \brief Update graph with datapoints from buffer based on current FPS
     * \param buffer Buffer object that holds the data
     */
    void updateGraph(Buffer& buffer, double timeInterval) override;

    /*!
     * \brief removeData Erases data from the graph between x0 and x1.
     * \param x0 Start
     * \param x1 End
     */
    void removeData(double const x0, double const x1);
    void reset() override;

    void drawLinePlot(QCPPainter* painter, const QVector<QPointF> &lines) const override;
    void drawPixmap(QCPPainter* painter, const QVector<QPointF> &lines) const;
    QPolygonF createPolygon(double pixelSize) const;
    QRectF clearRect() const;

private:

    mutable QPixmap mMemSignalPlot;
    QVector<QPointF> newLines;
};

#endif // TIMESIGNAL_H
