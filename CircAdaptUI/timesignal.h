#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H
#include "qcustomplot.h"
#include "buffer.h"

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
    TimeSignal(QCPAxis* xAxis, QCPAxis* yAxis, QString yVar, QString xVar = "t", QColor color = QColor(0,0,0)) :
        QCPGraph(xAxis, yAxis),
        m_yVar(yVar),
        m_xVar(xVar)
    {
        setPen(QPen(color, 2));
    };

    /*!
     * \brief Update graph with datapoints from buffer based on current FPS
     * \param buffer Buffer object that holds the data
     */
    void updateGraph(Buffer& buffer);

    /*!
     * \brief removeData Erases data from the graph between x0 and x1.
     * \param x0 Start
     * \param x1 End
     */
    void removeData(double const x0, double const x1);

    void displaySnapshot(const Buffer& buffer);

    QString getXVar() { return m_xVar; };
    QString getYVar() { return m_yVar; };


private:

    /*!
     * \brief Name of the variable plotted on the y-axis.
     */
    QString m_yVar;

    /*!
     * \brief Name of the variable plotted on the x-axis.
     */
    QString m_xVar;

    double m_xPos{0};
    int i{0};
    double m_dt{0.1};
};

#endif // TIMESIGNAL_H
