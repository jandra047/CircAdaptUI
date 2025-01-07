#include "graphgrid.h"
#include "CircAdaptUI/Graphs/signalgraph.h"
#include "CircAdaptUI/Graphs/mmode.h"
#include "CircAdaptUI/Signals/timesignal.h"
#include "CircAdaptUI/settings.h"

GraphGrid::GraphGrid(QWidget* parent, int rows, int cols) :
    QWidget(parent),
    gridLayout(this),
    rows(rows),
    cols(cols),
    leftMarginGroup(Q_NULLPTR)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            SignalGraph* plot = Q_NULLPTR;
            if (i != GraphGrid::MMODE)
            {
                plot = new SignalGraph(this, "Time [s]", yLabels[i]);

                auto sigs = Settings::instance().GraphGrid()[rowTypes[i]].toArray();
                for (auto s = sigs.cbegin(), end = sigs.cend(); s != end; ++s)
                {
                    TimeSignal* sig = new TimeSignal
                    (
                        plot->xAxis,
                        plot->yAxis,
                        s->toObject()["displayName"].toString(),
                        s->toObject()["name"].toString(),
                        "t",
                        QColor(s->toObject()["color"].toString()),
                        s->toObject()["isVisible"].toBool(),
                        s->toObject()["unit"].toString(),
                        s->toObject()["inMainMenu"].toBool(true)
                    );
                    plot->addSignal(sig);
                }
            }
            else
            {
                plot = new MMode(this);
                gridLayout.addWidget(plot, i, j);
            }

            if (j > 0)
            {
                plot->yAxis->setTicks(false);
                plot->yAxis->setTickLabels(false);
                plot->yAxis->setLabel("");
            }

            if (i == 0)
            {
                plot->setTitle(colTypes[j], QFont("Liberation Sans", 12, QFont::Bold));
            }
            gridLayout.addWidget(plot, i, j);
            if (j < ColType::CURRENT)
            {
                plot->setZoomPastX(false);
                plot->setShowTooltip(true);
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        setRowVisible(i, rowVisibility[i]);
    }
    connectRowYAxes();
    connectColXAxes();
    gridLayout.setContentsMargins(QMargins(0,0,0,0));
    gridLayout.setSpacing(0);
    gridLayout.setColumnStretch(0, 1);
    gridLayout.setColumnStretch(1, 1);
    gridLayout.setColumnStretch(2, 2);
    buildMenus();
    connectLineMarkers();
    updateLastRowTicksAndLabels();
    for (int i = 0; i < rows; i++)
    {
        getItem(i, ColType::CURRENT)->axisRect()->setMinimumMargins(QMargins(0,0,5,0));
    }
    connectLeftMargins();
}

GraphGrid::~GraphGrid()
{
    delete leftMarginGroup;
}

void GraphGrid::buildMenus()
{
    for (int i = 0; i < rows; i++)
    {
        if (i != RowType::MMODE)
        {
            auto pair = getItem(i, 0)->buildMenu(this);
            QObject::connect(pair.second, &QActionGroup::triggered, this, &GraphGrid::handleAction);
            for (int j = 0; j < cols; j++)
            {
                getItem(i, j)->setContextMenu(pair);
            }
        }

    }
}

SignalGraph* GraphGrid::getItem(int rowIdx, int colIdx)
{
    return dynamic_cast<SignalGraph*>(gridLayout.itemAtPosition(rowIdx, colIdx)->widget());
}

void GraphGrid::linkYAxis(SignalGraph* gc1, SignalGraph* gc2)
{
    QObject::connect(gc1->yAxis, SIGNAL(rangeChanged(QCPRange)), gc2->yAxis, SLOT(setRange(QCPRange)));
    QObject::connect(gc1->yAxis, qOverload<const QCPRange& >(&QCPAxis::rangeChanged), gc2, [=](const QCPRange& range) {
        gc2->yAxis->grid()->layer()->replot();
    });
}

void GraphGrid::linkXAxis(SignalGraph* gc1, SignalGraph* gc2)
{
    QObject::connect(gc1->xAxis, SIGNAL(rangeChanged(QCPRange)), gc2->xAxis, SLOT(setRange(QCPRange)));
    QObject::connect(gc1->xAxis, qOverload<const QCPRange& >(&QCPAxis::rangeChanged), gc2, [=](const QCPRange& range) {
        gc2->xAxis->grid()->layer()->replot();
    });
}

void GraphGrid::connectRowYAxes()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                if (j != k) {
                    linkYAxis(getItem(i, j), getItem(i, k));
                }
            }
        }
    }
}

void GraphGrid::connectColXAxes()
{
    for (int j = 0; j < cols; ++j)
    {
        for (int i = 0; i < rows; ++i) {
            for (int k = 0; k < rows; ++k) {
                if (i != k) {
                    linkXAxis(getItem(i, j), getItem(k, j));
                }
            }
        }
    }
}

void GraphGrid::updateGraphs(Buffer& buffer, double timeInterval)
{
    for (int i = 0; i < rows; i++)
    {
        getItem(i, ColType::CURRENT)->updateGraph(buffer, timeInterval);
    }
}

void GraphGrid::setRowVisible(int row, bool isVisible)
{
    for (int i = 0; i < cols; i++)
    {

        gridLayout.itemAtPosition(row, i)->widget()->setVisible(isVisible);
    }
    rowVisibility[row] = isVisible;
    updateLastRowTicksAndLabels();
}

void GraphGrid::rescaleAxes()
{
    rescaleYAxes();
}

void GraphGrid::rescaleYAxes()
{
    for (int i = 0; i < rows; i++)
    {

        double yMin = std::numeric_limits<double>::max();
        double yMax = std::numeric_limits<double>::lowest();

        for (int j = 0; j < cols; j++)
        {
            auto item = getItem(i, j);

            if (item->containsSignals())
            {
                QCPRange itemRange = item->getYDataRange();
                    if (itemRange.lower < yMin)
                        {
                            yMin = itemRange.lower;
                        }

                        if (itemRange.upper > yMax)
                        {
                            yMax = itemRange.upper;
                        }
            }
        }

        for (int j = 0; j < cols; j++)
        {
            auto item = getItem(i, j);
            double padding = (yMax - yMin) * Settings::instance().paddingVertical();
            item->yAxis->setRange(yMin - padding, yMax + padding);
        }
    }
}

void GraphGrid::replotFull(ColTypeFlags columns) {
    for (int i = 0; i < rows; i++) {
        if (columns.includes(ColType::REFERENCE)) {
            getItem(i, ColType::REFERENCE)->replot();
        }
        if (columns.includes(ColType::SNAPSHOT)) {
            getItem(i, ColType::SNAPSHOT)->replot();
        }
        if (columns.includes(ColType::CURRENT)) {
            getItem(i, ColType::CURRENT)->replot();
        }
    }
}

void GraphGrid::replot(ColTypeFlags columns) {
    for (int i = 0; i < rows; i++) {
        if (columns.includes(ColType::REFERENCE)) {
            getItem(i, ColType::REFERENCE)->currentLayer()->replot();
        }
        if (columns.includes(ColType::SNAPSHOT)) {
            getItem(i, ColType::SNAPSHOT)->currentLayer()->replot();
        }
        if (columns.includes(ColType::CURRENT)) {
            getItem(i, ColType::CURRENT)->currentLayer()->replot();
        }
    }
}

void GraphGrid::takeSnapshot(Buffer& buffer)
{
    for (int i = 0; i < rows; i++)
    {
        auto item = getItem(i, 1);
        item->displaySnapshot(buffer);
        item->xAxis->rescale();
    }
}

void GraphGrid::displayReference(Buffer& buffer)
{
    for (int i = 0; i < rows; i++)
    {
        auto item = getItem(i, 0);
        item->displaySnapshot(buffer);
        item->xAxis->rescale();
    }
}

void GraphGrid::handleAction(QAction* a)
{
    auto pos = findGridIndex(a->parent());
    int row = pos.first;

    if (pos != std::pair<int, int>(-1, -1))
    {
        for (int j = 0; j < cols; j++)
        {
            auto item = getItem(row, j);
            item->showSignal(a);
            item->replot();
        }
    }
}

void GraphGrid::connectLineMarkers()
{
    for (int j = 0; j < ColType::CURRENT; ++j)
    {
        for (int i = 0; i < rows; ++i) {
            auto itemA = getItem(i, j);
            for (int k = 0; k < rows; ++k)
            {
                if (i != k)
                {
                    auto itemB = getItem(k, j);

                    for (auto item : { itemA, itemB })
                    {
                        if (item->getLineMarker() == Q_NULLPTR)
                        {
                            item->setLineMarker(new LineMarker(item));
                        }
                    }
                    connect(itemA->getLineMarker(), &LineMarker::xPosChanged, itemB->getLineMarker(), &LineMarker::setXPos);

                }
            }
            connect(itemA->getLineMarker(), &LineMarker::xPosChanged, this, [=](double x){ emit verticalLineDrawn(static_cast<ColType>(j), x); } );
        }
    }
}

void GraphGrid::updateLastRowTicksAndLabels() {
    // Hide ticks and labels for all rows
    for (int i = 0; i < rows; i++)
    {
        if (rowVisibility[i])
        {
            for (int j = 0; j < cols; j++)
            {
                auto item = getItem(i, j);
                item->xAxis->setTicks(false);
                item->xAxis->setTickLabels(false);
                item->xAxis->setLabel("");
                item->layer("axes")->replot();
            }
        }
    }

    // Find the last visible row and show ticks and labels
    for (int i = rows - 1; i >= 0; i--)
    {
        if (rowVisibility[i])
        {
            for (int j = 0; j < cols; j++)
            {
                auto item = getItem(i, j);
                item->xAxis->setTicks(true);
                item->xAxis->setTickLabels(true);
                item->xAxis->setLabel("Time [s]");
                item->layer("axes")->replot();
            }
            break; // Exit loop after updating the last visible row
        }
    }
}

void GraphGrid::connectLeftMargins()
{
    leftMarginGroup = new QCPMarginGroup(getItem(0,0));
    for (int i = 0; i < rows; i++)
    {
        auto item = getItem(i, ColType::REFERENCE);
        item->axisRect()->setMarginGroup(QCP::msLeft, leftMarginGroup);
    }
}

void GraphGrid::clearSnapshot()
{
    for (int i = 0; i < rows; i++)
    {
        auto item = getItem(i, ColType::SNAPSHOT);
        item->clearSignals();
    }

}

void GraphGrid::clearGraphData()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            auto item = getItem(i, j);
            item->clearSignals();
            if (item->getLineMarker())
                item->getLineMarker()->setVisible(false);
            item->replot();
        }
    }
}
