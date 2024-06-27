#ifndef GRAPHGRID_H
#define GRAPHGRID_H

#include <QWidget>
#include <QGridLayout>
#include "buffer.h"
#include "timesignal.h"
#include "graphcontainer.h"

/*!
 * \brief Contains a grid which holds \ref GraphContainer objects.
 */
class GraphGrid : public QWidget
{
    Q_OBJECT

    enum ColType {
        REFERENCE,
        SNAPSHOT,
        CURRENT
    };

    enum RowType {
        PRESSURES,
        VOLUMES,
        FLOWS
    };
    const QVector<QString> colTypes = {"REFERENCE", "SNAPSHOT", "CURRENT"};
    const QVector<QString> rowTypes = {"PRESSURES", "VOLUMES", "FLOWS"};
    const QVector<QString> yLabels = {"Pressure [mmHg]", "Volume [mL]", "Flow [L/min]"};

public:
    GraphGrid(QWidget*, int rows = 3, int cols = 3);

    void setupSignals();

    /*!
     * \brief Access an element of the grid.
     * \param rowIdx Row index
     * \param colIdx Column index
     * \return An item in the grid
     */
    GraphContainer<TimeSignal>* getItem(int rowIdx, int colIdx);

    /*!
     * \brief Hides or shows a row in a grid
     * \param rowIdx Index of the row
     * \param isVisible Show or hide the row
     */
    void setRowVisible(int rowIdx, bool isVisible);

    /*!
     * \brief Rescales all axes in the grid based on signals which are currently visible.
     * \param onlyVisiblePlottables
     */
    void rescaleAxes(bool onlyVisiblePlottables);

    /*!
     * \brief Rescales y-axes in the grid based on signals which are currently visible.
     * \param onlyVisiblePlottables
     */
    void rescaleYAxes(bool onlyVisiblePlottables);

    /*!
     * \brief Calls a replot() function on all graphs within the grid.
     *
     * After modifying the data of the signals in graphs, replot() needs to
     * be called in order to visualize these changes in the plots.
     */
    void replot();

    /*!
     * \brief Connects the y-axis ranges of all graphs in a row.
     */
    void connectRowYAxes();

    /*!
     * \brief Connects the x-axis (time) ranges of all graphs in a column.
     */
    void connectColXAxes();

    /*!
     * \brief Links y-axes of 2 \ref GraphContainers.
     * \param gc1 First container
     * \param gc2 Second container
     */
    void linkYAxis(GraphContainer<TimeSignal>* gc1, GraphContainer<TimeSignal>* gc2);

    /*!
     * \brief Links x-axes of 2 \ref GraphContainers.
     * \param gc1 First container
     * \param gc2 Second container
     */
    void linkXAxis(GraphContainer<TimeSignal>* gc1, GraphContainer<TimeSignal>* gc2);

    double getReplottime() { return getItem(0,2)->replotTime(); };

public slots:

    /*!
     * \brief Updates all graphs within the grid.
     * \param buffer Buffer to update the graphs from.
     */
    void updateGraphs(Buffer& buffer);

private:
    QGridLayout gridLayout;

    /*!
     * \brief Number of rows in a grid.
     */
    int rows;

    /*!
     * \brief Number of columns in the grid.
     */
    int cols;
};
#endif // GRAPHGRID_H
