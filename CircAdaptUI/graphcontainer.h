#ifndef GRAPHCONTAINER_H
#define GRAPHCONTAINER_H
#include "dependencies/qcustomplot.h"
#include "buffer.h"
// #include "signalslothelper.h"

class SignalSlotHelper : public QObject {
    Q_OBJECT

public:
    SignalSlotHelper(QObject* parent = nullptr) : QObject(parent) {}

signals:
    void actionTriggered(QAction*);
};

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
    ~GraphContainer();

    /*!
     * \brief Updates the signals plotted on the graph container from the data from the buffer.
     * \param buffer Buffer from which to update the graph.
     */
    void updateGraph(Buffer& buffer);

    /*!
     * \brief Adds a signal to the container.
     */
    void addSignal(ptr_type);

    /*!
     * \brief Get the minimum and maximum value of signals plotted in graph container
     * \return QCPRange containing min and max value of signals plotted in graph container
     */
    QCPRange getYDataRange();

    /*!
     * \brief Check if graph container contains any signals
     * \return True if contains signals
     */
    bool containsSignals();

    void displaySnapshot(Buffer& buffer);

    void showToolTip(QMouseEvent *event);

    virtual QString getPoint(const QPoint& pos) = 0;
    std::pair<QMenu*, QActionGroup*> buildMenu(QWidget* parent);
    SignalSlotHelper* helper;
    void showSignal(QAction* action);
    void setContextMenu(const std::pair<QMenu*, QActionGroup*>& menu);
private:

    /*!
     * \brief Handles different zoom functionalities.
     * \param e QWheelEvent which holds data on wheel turn.
     */
    void zoom(QWheelEvent* event);

    QMenu* contextMenu;
    QActionGroup* actionGroup;

protected:
    /*!
     * \brief Contains signals which are plotted in this container.
     */
    QVector<ptr_type> m_Signals;
};

#endif // GRAPHCONTAINER_H
