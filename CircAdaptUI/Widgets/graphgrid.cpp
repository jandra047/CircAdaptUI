#include "graphgrid.h"
#include "CircAdaptUI/Graphs/signalgraph.h"
#include "CircAdaptUI/Signals/timesignal.h"
#include "CircAdaptUI/settings.h"

GraphGrid::GraphGrid(QWidget* parent, int rows, int cols) :
    QWidget(parent),
    gridLayout(this),
    rows(rows),
    cols(cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            SignalGraph* plot = new SignalGraph(this, "Time [s]", yLabels[i]);

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
                    s->toObject()["unit"].toString()
                );
                plot->addSignal(sig);
            }
            if (j > 0)
            {
                plot->yAxis->setTicks(false);
                plot->yAxis->setTickLabels(false);
                plot->yAxis->setLabel("");
            }
            if (i < (rows - 1))
            {
                plot->xAxis->setTicks(false);
                plot->xAxis->setTickLabels(false);
                plot->xAxis->setLabel("");
            }
            if (i == 0)
            {
                plot->plotLayout()->insertRow(0);
                QCPTextElement *title = new QCPTextElement(plot, colTypes[j], QFont("Mononoki", 12, QFont::Bold));
                plot->plotLayout()->addElement(0,0, title);
            }
            gridLayout.addWidget(plot, i, j);
        }
    }
    setRowVisible(3, false);
    setRowVisible(4, false);
    connectRowYAxes();
    connectColXAxes();
    gridLayout.setContentsMargins(QMargins(0,0,0,0));
    gridLayout.setSpacing(0);
    gridLayout.setColumnStretch(0, 1);
    gridLayout.setColumnStretch(1, 1);
    gridLayout.setColumnStretch(2, 2);
    buildMenus();
}

GraphGrid::~GraphGrid()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            delete getItem(i,j);
        }
    }

}

void GraphGrid::buildMenus()
{
    for (int i = 0; i < rows; i++)
    {
        auto pair = getItem(i, 0)->buildMenu(this);
        QObject::connect(pair.second, &QActionGroup::triggered, this, &GraphGrid::handleAction);
        for (int j = 0; j < cols; j++)
        {
            getItem(i, j)->setContextMenu(pair);
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

void GraphGrid::updateGraphs(Buffer& buffer)
{
    for (int i = 0; i < rows; i++)
    {
        getItem(i, ColType::CURRENT)->updateGraph(buffer);

    }
}

void GraphGrid::setRowVisible(int row, bool isVisible)
{
    for (int i = 0; i < cols; i++)
    {
        gridLayout.itemAtPosition(row, i)->widget()->setVisible(isVisible);
    }
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
    replot();
}

void GraphGrid::replot()
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            getItem(i, j)->replot();
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
            getItem(row, j)->showSignal(a);
        }
    }
}
