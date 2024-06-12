#ifndef GRAPHGRID_H
#define GRAPHGRID_H

#include <QWidget>
#include <QGridLayout>
#include "buffer.h"

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
    const QVector<QString> types = {"REFERENCE", "SNAPSHOT", "CURRENT"};

public:
    GraphGrid(QWidget*, int rows = 2, int cols = 3);

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
     * \brief Calls a replot() function on all graphs within the grid.
     *
     * After modifying the data of the signals in graphs, replot() needs to
     * be called in order to visualize these changes in the plots.
     */
    void replot();

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
