#include "graphgrid.h"
#include "signalgraph.h"
#include "timesignal.h"

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
            SignalGraph* plot = new SignalGraph(this);
            if (j == ColType::CURRENT)
            {
                if (i == 0)
                {
                    TimeSignal* sig = new TimeSignal(plot->xAxis, plot->yAxis, "pLv", "t", QColor(227, 26, 28));
                    TimeSignal* sig2 = new TimeSignal(plot->xAxis, plot->yAxis, "pRv", "t", QColor(31, 120, 180));
                    plot->addSignal(sig);
                    plot->addSignal(sig2);
                }
                if (i == 1)
                {
                    TimeSignal* sig = new TimeSignal(plot->xAxis, plot->yAxis, "VLv", "t", QColor(227, 26, 28));
                    TimeSignal* sig2 = new TimeSignal(plot->xAxis, plot->yAxis, "VRv", "t", QColor(31, 120, 180));
                    plot->addSignal(sig);
                    plot->addSignal(sig2);
                }
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
                QCPTextElement *title = new QCPTextElement(plot, types[j], QFont("Mononoki", 12, QFont::Bold));
                plot->plotLayout()->addElement(0,0, title);
            }
        gridLayout.addWidget(plot, i, j);
        }
    }
    connectRowYAxes();
    connectColXAxes();
    gridLayout.setContentsMargins(QMargins(0,0,0,0));
    gridLayout.setSpacing(0);
    gridLayout.setColumnStretch(0, 1);
    gridLayout.setColumnStretch(1, 1);
    gridLayout.setColumnStretch(2, 2);
}


GraphContainer<TimeSignal>* GraphGrid::getItem(int rowIdx, int colIdx)
{
    return dynamic_cast<GraphContainer<TimeSignal>*>(gridLayout.itemAtPosition(rowIdx, colIdx)->widget());
}

void GraphGrid::linkYAxis(GraphContainer<TimeSignal>* gc1, GraphContainer<TimeSignal>* gc2)
{
    QObject::connect(gc1->yAxis, SIGNAL(rangeChanged(QCPRange)), gc2->yAxis, SLOT(setRange(QCPRange)));
    QObject::connect(gc1->yAxis, qOverload<const QCPRange& >(&QCPAxis::rangeChanged), gc2, [=](const QCPRange& range) {
        gc2->yAxis->grid()->layer()->replot();
    });
}

void GraphGrid::linkXAxis(GraphContainer<TimeSignal>* gc1, GraphContainer<TimeSignal>* gc2)
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
                if (j != k) {
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
        dynamic_cast<GraphContainer<TimeSignal>*>(gridLayout.itemAtPosition(i, ColType::CURRENT)->widget())->updateGraph(buffer);

    }
}

void GraphGrid::setRowVisible(int row, bool isVisible)
{
    for (int i = 0; i < cols; i++)
    {
        gridLayout.itemAtPosition(row, i)->widget()->setVisible(isVisible);
    }
}

void GraphGrid::rescaleAxes(bool onlyVisiblePlottables)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dynamic_cast<GraphContainer<TimeSignal>*>(gridLayout.itemAtPosition(i, j)->widget())->rescaleAxes(onlyVisiblePlottables);
        }
    }
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
