#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H
#include "dependencies/qcustomplot.h"
#include "CircAdaptUI/buffer.h"

/*!
 * \brief Wraps a QCPGraph class which contains a time signal.
 */
class TimeSignal : public QCPGraph
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
        color(color),
        m_yVar(yVar),
        m_xVar(xVar),
        m_displayName(displayName),
        m_unit(unit),
        m_isInMainMenu(isInMainMenu)
    {
        setPen(QPen(color, 2));
        setVisible(isVisible);
    };
    ~TimeSignal() {};
    /*!
     * \brief Update graph with datapoints from buffer based on current FPS
     * \param buffer Buffer object that holds the data
     */
    void updateGraph(Buffer& buffer, double timeInterval);

    /*!
     * \brief removeData Erases data from the graph between x0 and x1.
     * \param x0 Start
     * \param x1 End
     */
    void removeData(double const x0, double const x1);

    const QString getXVar() const { return m_xVar; };
    const QString getYVar() const { return m_yVar; };
    const QColor getColor() const { return color; }
    const QString getDisplayName() const { return m_displayName; }
    const QString getUnit() const { return m_unit; }
    bool isInMainMenu() { return m_isInMainMenu; }
    void drawLinePlot(QCPPainter* painter, const QVector<QPointF> &lines) const override;
    void drawPixmap(QCPPainter* painter, const QVector<QPointF> &lines) const;
    QPolygonF createPolygon(double pixelSize) const;
    QRectF clearRect() const;
    void reset();
    double timeInt;

private:

    /*!
     * \brief Name of the variable plotted on the y-axis.
     */
    QString m_yVar;

    /*!
     * \brief Name of the variable plotted on the x-axis.
     */
    QString m_xVar;

    bool m_isInMainMenu;

    QString m_displayName;

    QString m_unit;

    QColor color;

    double m_xPos{0};
    int i{0};
    double m_dt{0.2};
    mutable QPixmap mMemSignalPlot;
    QVector<QPointF> newLines;
};

#endif // TIMESIGNAL_H
