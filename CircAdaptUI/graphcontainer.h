#ifndef GRAPHCONTAINER_H
#define GRAPHCONTAINER_H
#include "dependencies/qcustomplot.h"
#include "buffer.h"

/*!
 * \brief Contains signals.
 * \tparam SignalType Type of signals which GraphContainer contains.
 * Can be \ref TimeSignal or \ref LoopSignal
 *
 * GraphContainer wraps a QCustomPlot class. It contains signals which are either of type \ref TimeSignal or type \ref LoopSignal,
 * handles adding new signals and updating them from buffer.
 */
template<typename SignalType>
class GraphContainer : public QCustomPlot
{
public:
    using ptr_type = SignalType*;
    GraphContainer(QWidget* parent = Q_NULLPTR);
    ~GraphContainer() = default;

    /*!
     * \brief Updates the signals plotted on the graph container from the data from the buffer.
     * \param buffer Buffer from which to update the graph.
     */
    void updateGraph(Buffer& buffer, double timeInterval);

    /*!
     * \brief Adds a signal to the container.
     */
    virtual void addSignal(ptr_type);

    /*!
     * \brief Get the minimum and maximum yAxis value of signals plotted in graph container
     * \return QCPRange containing yAxis min and max value of signals plotted in graph container
     */
    QCPRange getYDataRange();

    /*!
     * \brief Get the minimum and maximum xAxis value of signals plotted in graph container
     * \return QCPRange containing xAxis min and max value of signals plotted in graph container
     */
    QCPRange getXDataRange();

    /*!
     * \brief Check if graph container contains any signals
     * \return True if contains signals
     */
    bool containsSignals();

    virtual void displaySnapshot(Buffer& buffer) = 0;

    void showTooltip(QMouseEvent *event);

    virtual QString getPoint(const QPoint& pos) = 0;
    std::pair<QMenu*, QActionGroup*> buildMenu(QWidget* parent);
    virtual void showSignal(QAction* action);
    void setContextMenu(const std::pair<QMenu*, QActionGroup*>& menu);
    void setTitle(QString title, QFont font);
    void setZoomPastX(bool zoomPastX) { m_zoomPastX = zoomPastX; };
    void setShowTooltip(bool isShowTooltip) { m_showTooltip = isShowTooltip; }
    bool getZoomPastX() { return m_zoomPastX; };
    bool isEmpty();
    const QVector<ptr_type>& getSignals() const { return m_Signals; }
    const bool getShowTooltip() const { return m_showTooltip; }
private:

    /*!
     * \brief Handles different zoom functionalities.
     * \param e QWheelEvent which holds data on wheel turn.
     */
    virtual void zoom(QWheelEvent* event);

    QActionGroup* actionGroup;

protected:
    /*!
     * \brief Contains signals which are plotted in this container.
     */
    QVector<ptr_type> m_Signals;
    QCPTextElement* title;
    bool m_zoomPastX;
    double getMaxX();
    QMenu* contextMenu;
    bool m_showTooltip;
    void runEraser();
    double m_eraserWidth = 0.2;

public slots:
    void clearSignals();
};

#endif // GRAPHCONTAINER_H
