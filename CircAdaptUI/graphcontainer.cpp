#include "graphcontainer.h"
#include "CircAdaptUI/Signals/loopsignal.h"
#include "CircAdaptUI/Signals/timesignal.h"

template<typename SignalType>
GraphContainer<SignalType>::GraphContainer(QWidget* parent) :
    QCustomPlot(parent),
    contextMenu(new QMenu(this)),
    actionGroup(new QActionGroup(this))
{
    setOpenGl(true);
    currentLayer()->setMode(QCPLayer::lmBuffered);
    setInteraction(QCP::iRangeDrag);
    xAxis->ticker()->setTickCount(5);
    xAxis->setTickLabelFont(QFont("Times", 12, QFont::Bold));
    xAxis->grid()->setPen(QPen(QColor(0xd0d0d0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    yAxis->ticker()->setTickCount(5);
    yAxis->setTickLabelFont(QFont("Times", 12, QFont::Bold));
    yAxis->grid()->setPen(QPen(QColor(0xaaaaaa), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setBackground(QColor(0xededed));
    setBackground(QColor(0xaaaaaa));
    yAxis->setRange(0,200);
    xAxis->setRange(0,3);
    setContextMenuPolicy(Qt::CustomContextMenu);

    // connect(this, &QCustomPlot::customContextMenuRequested, this, &GraphContainer::menu);
    connect(this, &QCustomPlot::customContextMenuRequested, this, [=](const QPoint& p) {
        contextMenu->exec(mapToGlobal(p));
    });
    connect(this, &QCustomPlot::mouseWheel, this, &GraphContainer::zoom);
    connect(this, &QCustomPlot::mouseMove, this, &GraphContainer::showToolTip);
}

template<typename SignalType>
GraphContainer<SignalType>::~GraphContainer()
{
    while (m_Signals.count())
    {
        delete m_Signals.takeLast();
    }

}

template<typename SignalType>
void GraphContainer<SignalType>::buildMenu()
{
    contextMenu->clear();
    actionGroup->setExclusive(false); // Allow multiple actions to be checked/unchecked

    for (int i = 0; i < m_Signals.size(); ++i) {
        QAction *action = new QAction(m_Signals[i]->getYVar(), this);
        QPixmap pixmap(16, 16);
        QPixmap     disabledPixmap( 8, 8 );     // Used for the wall patched when all signals for the whole wall are being shown
        QIcon icon;
        pixmap.fill(m_Signals[i]->getColor());
        disabledPixmap.fill( m_Signals.at( i )->getColor() );

        icon.addPixmap( pixmap, QIcon::Active );
        icon.addPixmap( disabledPixmap, QIcon::Disabled );

        action->setIcon(icon);
        action->setCheckable(true);
        action->setChecked(m_Signals[i]->visible());
        action->setData(i); // Store the index of the signal in the action
        // connect(action, &QAction::triggered, this, &GraphContainer::showHideSignal);
        contextMenu->addAction(action);
        actionGroup->addAction(action);
        QFont actionFont = action->font();
        actionFont.setBold(action->isChecked());
        action->setFont(actionFont);
    }
    QObject::connect(actionGroup, &QActionGroup::triggered, this, &GraphContainer::on_contextMenu);
}

template<typename SignalType>
void GraphContainer<SignalType>::addSignal(SignalType* signal)
{
    signal->setLayer(this->currentLayer());
    m_Signals.push_back(signal);
}

template<typename SignalType>
void GraphContainer<SignalType>::on_contextMenu(QAction* action)
{
    QFont actionFont = action->font();
    actionFont.setBold(action->isChecked());
    action->setFont(actionFont);
    m_Signals[action->data().toInt()]->setVisible(action->isChecked());
    mCurrentLayer->replot();
}


template<typename SignalType>
void GraphContainer<SignalType>::zoom(QWheelEvent* event)
{
    // Calculate the zoom factor based on the wheel angle delta
    double zoomFactor = 1 - event->angleDelta().y() / 1200.0; // Adjust as needed

    if (event->modifiers() & Qt::ShiftModifier)
    {
        xAxis->setRangeUpper(xAxis->range().upper * zoomFactor);
    }
    else
    {
        yAxis->setRangeUpper(yAxis->range().upper * zoomFactor);
    }

    replot();

    // Accept the event to prevent further processing
    event->accept();
}

template<typename SignalType>
void GraphContainer<SignalType>::updateGraph(Buffer& buffer)
{
    for (int i = 0; i < m_Signals.size(); i++)
    {
        m_Signals[i]->updateGraph(buffer);
    }
    currentLayer()->replot();
}

template<typename SignalType>
QCPRange GraphContainer<SignalType>::getYDataRange()
{
    double yMax = std::numeric_limits<double>::lowest();
    double yMin = std::numeric_limits<double>::max();

    for (int i = 0; i < m_Signals.size(); i++)
    {
        bool isFound;
        auto yRange = m_Signals[i]->data()->valueRange(isFound);
        if (isFound)
        {
            if (yRange.upper > yMax)
              yMax = yRange.upper;
            if (yRange.lower < yMin)
              yMin = yRange.lower;
        }
    }
    return QCPRange(yMin, yMax);
}

template<typename SignalType>
bool GraphContainer<SignalType>::containsSignals()
{
    if (m_Signals.size() > 0)
    {
        for (auto signal : m_Signals)
        {
            if (!signal->data()->isEmpty())
            {
                return true;
            }
        }
    }
    return false;
}

template<typename SignalType>
void GraphContainer<SignalType>::displaySnapshot(Buffer& buffer)
{
    for (int i = 0; i < m_Signals.size(); i++)
    {
        m_Signals[i]->displaySnapshot(buffer);
    }
    currentLayer()->replot();
}

template<typename SignalType>
void GraphContainer<SignalType>::showToolTip(QMouseEvent *event) {
    if (containsSignals())
    {
        double x = xAxis->pixelToCoord(event->pos().x());
        QString text = getPoint(event->pos());
        QToolTip::showText(event->globalPosition().toPoint(), text, this);
    }
}

template class GraphContainer<LoopSignal>;
template class GraphContainer<TimeSignal>;
