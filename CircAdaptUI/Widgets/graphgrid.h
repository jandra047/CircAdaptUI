#ifndef GRAPHGRID_H
#define GRAPHGRID_H

#include <QWidget>
#include <QGridLayout>
#include "CircAdaptUI/buffer.h"
#include "CircAdaptUI/Graphs/signalgraph.h"

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
        PRESSURE,
        VOLUME,
        FLOW,
        STRESS,
        STRAIN
    };
    const QVector<QString> colTypes = {"REFERENCE", "SNAPSHOT", "CURRENT"};
    const QVector<QString> rowTypes = {"PRESSURE", "VOLUME", "FLOW", "STRESS", "STRAIN"};
    const QVector<QString> yLabels = {"Pressure [mmHg]", "Volume [mL]", "Flow [mL/s]", "Stress [Pa]", "Strain [-]"};

public:
    GraphGrid(QWidget*, int rows = 5, int cols = 3);

    void setupSignals();

    /*!
     * \brief Access an element of the grid.
     * \param rowIdx Row index
     * \param colIdx Column index
     * \return An item in the grid
     */
    SignalGraph* getItem(int rowIdx, int colIdx);

    /*!
     * \brief Hides or shows a row in a grid
     * \param rowIdx Index of the row
     * \param isVisible Show or hide the row
     */
    void setRowVisible(int rowIdx, bool isVisible);

    /*!
     * \brief Rescales all axes in the grid based on signals which are currently visible.
     */
    void rescaleAxes();

    /*!
     * \brief Rescales y-axes in the grid based on signals which are currently visible.
     * \param onlyVisiblePlottables
     */
    void rescaleYAxes();

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
    void linkYAxis(SignalGraph* gc1, SignalGraph* gc2);

    /*!
     * \brief Links x-axes of 2 \ref GraphContainers.
     * \param gc1 First container
     * \param gc2 Second container
     */
    void linkXAxis(SignalGraph* gc1, SignalGraph* gc2);

    double getReplottime() { return getItem(0,2)->replotTime(); };

    void printOpenGL() {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                qDebug() << getItem(i,j)->openGl() << " ";
            }
        }
        qDebug() << "\n";
    }

public slots:

    /*!
     * \brief Updates all graphs within the grid.
     * \param buffer Buffer to update the graphs from.
     */
    void updateGraphs(Buffer& buffer);

    void takeSnapshot(Buffer& buffer);

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
