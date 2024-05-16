#include "graphgrid.h"
#include "graphcontainer.h"
#include "timesignal.h"

GraphGrid::GraphGrid(int rows, int cols, QWidget* parent) :
    QWidget(parent),
    gridLayout(this),
    rows(rows),
    cols(cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            GraphContainer<TimeSignal>* plot = new GraphContainer<TimeSignal>(this);
            if (j == ColType::CURRENT)
            {
                plot->createSignals(2);
            }
            if (j > 0)
            {
                plot->yAxis->setTicks(false);
            }
            if (i < (rows - 1))
            {
                plot->xAxis->setTicks(false);
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
    gridLayout.setContentsMargins(QMargins(0,0,0,0));
    gridLayout.setSpacing(0);
    gridLayout.setColumnStretch(0, 1);
    gridLayout.setColumnStretch(1, 1);
    gridLayout.setColumnStretch(2, 2);
}

void GraphGrid::updateGraphs(Buffer& buffer)
{
    for (int i = 0; i < rows; i++)
    {
        dynamic_cast<GraphContainer<TimeSignal>*>(gridLayout.itemAtPosition(i, ColType::CURRENT)->widget())->updateGraph2(buffer);

    }
}
