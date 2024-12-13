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

public:
    enum ColType {
        REFERENCE = 0,
        SNAPSHOT = 1,
        CURRENT = 2,
        ALL = -1
    };

    // Helper struct to handle flag operations
    struct ColTypeFlags {
        unsigned int flags;

        // Convert from single ColType to flags
        explicit ColTypeFlags(ColType type) {
            if (type == ColType::ALL) {
                flags = (1u << 3) - 1;  // Set all bits up to highest column
            } else {
                flags = 1u << static_cast<unsigned int>(type);
            }
        }

        // Convert from raw flags
        explicit ColTypeFlags(unsigned int f) : flags(f) {}

        bool includes(ColType type) const {
            return (flags & (1u << static_cast<unsigned int>(type))) != 0;
        }

        static ColTypeFlags all() {
            return ColTypeFlags(ColType::ALL);
        }
    };


    enum RowType {
        PRESSURE,
        VOLUME,
        FLOW,
        STRESS,
        STRAIN,
        SATURATION,
        MMODE
    };
    const QVector<QString> colTypes = {"REFERENCE", "SNAPSHOT", "CURRENT"};
    const QVector<QString> rowTypes = {"PRESSURE", "VOLUME", "FLOW", "STRESS", "STRAIN", "SATURATION", "MMODE"};
    const QVector<QString> yLabels = {"Pressure [mmHg]", "Volume [mL]", "Flow velocity [cm/s]", "Stress [kPa]", "Strain [%]", "Saturation [%]", "MMode"};

public:
    GraphGrid(QWidget*, int rows = 7, int cols = 3);
    ~GraphGrid();

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
    void replot(ColTypeFlags columns = ColTypeFlags::all());
    void replot(ColType column) { replot(ColTypeFlags(column)); }


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

signals:
    void verticalLineDrawn(ColType colType, double x);

public slots:

    /*!
     * \brief Updates all graphs within the grid.
     * \param buffer Buffer to update the graphs from.
     */
    void updateGraphs(Buffer& buffer, double timeInterval);

    void clearGraphData();

    void takeSnapshot(Buffer& buffer);
    void displayReference(Buffer& buffer);
    void handleAction(QAction* a);
    void clearSnapshot();

private:
    QGridLayout gridLayout;
    QVector<bool> rowVisibility = {true, true, true, false, false, false, false};

    std::pair<int, int> findGridIndex(QObject* target) {

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                QLayoutItem* item = gridLayout.itemAtPosition(i, j);
                if (item) {
                    QWidget* widget = item->widget();
                    if (widget == target) {
                        return {i, j};
                    }
                }
            }
        }
        return {-1, -1}; // Not found
    }
    /*!
     * \brief Number of rows in a grid.
     */
    int rows;

    /*!
     * \brief Number of columns in the grid.
     */
    int cols;

    QVector<std::pair<QMenu*, QActionGroup*>> contextMenus;
    void buildMenus();
    void connectLineMarkers();
    void updateLastRowTicksAndLabels();
    void connectLeftMargins();
    QCPMarginGroup* leftMarginGroup;
};

inline GraphGrid::ColTypeFlags operator|(GraphGrid::ColType a, GraphGrid::ColType b) {
    return GraphGrid::ColTypeFlags(
        (1u << static_cast<unsigned int>(a)) |
        (1u << static_cast<unsigned int>(b))
        );
}

inline GraphGrid::ColTypeFlags operator|(GraphGrid::ColTypeFlags a, GraphGrid::ColType b) {
    return GraphGrid::ColTypeFlags(a.flags | (1u << static_cast<unsigned int>(b)));
}

inline GraphGrid::ColTypeFlags operator|(GraphGrid::ColType a, GraphGrid::ColTypeFlags b) {
    return b | a;
}

inline GraphGrid::ColTypeFlags operator|(GraphGrid::ColTypeFlags a, GraphGrid::ColTypeFlags b) {
    return GraphGrid::ColTypeFlags(a.flags | b.flags);
}


#endif // GRAPHGRID_H
