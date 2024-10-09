#include "graphcontainer.h"
#include "CircAdaptUI/Signals/loopsignal.h"
#include "CircAdaptUI/Signals/timesignal.h"

template<typename SignalType>
GraphContainer<SignalType>::GraphContainer(QWidget* parent) :
    QCustomPlot(parent),
    contextMenu(Q_NULLPTR),
    actionGroup(Q_NULLPTR),
    title(Q_NULLPTR),
    m_zoomPastX(true)
{
    setOpenGl(true);

    QFont tickLabelFont = xAxis->labelFont();
    tickLabelFont.setPointSize(11);

    QFont labelFont = xAxis->labelFont();
    labelFont.setBold(true);
    labelFont.setPointSize(12);

    setPlottingHint(QCP::phCacheLabels, false);
    currentLayer()->setMode(QCPLayer::lmBuffered);
    setInteraction(QCP::iRangeDrag);
    xAxis->ticker()->setTickCount(4);
    xAxis->setTickLabelFont(tickLabelFont);
    xAxis->setLabelFont(labelFont);
    xAxis->grid()->setPen(QPen(QColor(0xcccccc), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    yAxis->ticker()->setTickCount(3);
    yAxis->setTickLabelFont(tickLabelFont);
    yAxis->setLabelFont(labelFont);
    yAxis->grid()->setPen(QPen(QColor(0xcccccc), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    axisRect()->setBackground(QColor(0xededed));
    setBackground(QColor(0xaaaaaa));
    yAxis->setRange(0,200);
    xAxis->setRange(0,3);
    setContextMenuPolicy(Qt::CustomContextMenu);

    plotLayout()->setMargins(QMargins(0, 5, 5, 0));
    plotLayout()->setOuterRect(QRect(0,0,0,0));
    plotLayout()->setColumnSpacing(0);
    plotLayout()->setRowSpacing(0);
    setContentsMargins(QMargins(0,0,0,0));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(0,0);
    axisRect()->setMinimumMargins(QMargins(0,0,0,0));
    axisRect()->setMargins(QMargins(0,0,0,0));

    connect(this, &QCustomPlot::customContextMenuRequested, this, [=](const QPoint& p) {
        contextMenu->exec(mapToGlobal(p));
    });
    connect(this, &QCustomPlot::mouseWheel, this, &GraphContainer::zoom);
    connect(this, &QCustomPlot::mouseMove, this, &GraphContainer::showToolTip);
}

template<typename SignalType>
std::pair<QMenu*, QActionGroup*> GraphContainer<SignalType>::buildMenu(QWidget* parent)
{
    QMenu* menu = new QMenu(parent);
    QActionGroup* actionGroup = new QActionGroup(parent);
    actionGroup->setExclusive(false); // Allow multiple actions to be checked/unchecked

    for (int i = 0; i < m_Signals.size(); ++i) {
        QAction *action = new QAction(m_Signals[i]->getDisplayName(), this);
        QPixmap pixmap(16, 16);
        QPixmap disabledPixmap( 8, 8 );     // Used for the wall patched when all signals for the whole wall are being shown
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
        menu->addAction(action);
        actionGroup->addAction(action);
        QFont actionFont = action->font();
        actionFont.setBold(action->isChecked());
        action->setFont(actionFont);
    }
    return std::pair<QMenu*, QActionGroup*> {menu, actionGroup};
}

template<typename SignalType>
void GraphContainer<SignalType>::addSignal(SignalType* signal)
{
    signal->setLayer(this->currentLayer());
    m_Signals.push_back(signal);
}

template<typename SignalType>
void GraphContainer<SignalType>::showSignal(QAction* action)
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

    if (event->modifiers() && Qt::ShiftModifier)
    {
        double max_X = getMaxX();
        if (xAxis->range().upper * zoomFactor > max_X && !m_zoomPastX && !isEmpty())
            xAxis->setRangeUpper(max_X);
        else
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
void GraphContainer<SignalType>::updateGraph(Buffer& buffer, double timeInterval)
{
    for (int i = 0; i < m_Signals.size(); i++)
    {
        m_Signals[i]->updateGraph(buffer, timeInterval);
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
        if (m_Signals[i]->visible())
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
void GraphContainer<SignalType>::showToolTip(QMouseEvent *event) {
    if (containsSignals())
    {
        double x = xAxis->pixelToCoord(event->pos().x());
        QString text = getPoint(event->pos());
        setToolTip(text);
    }
}

template<typename SignalType>
void GraphContainer<SignalType>::setContextMenu(const std::pair<QMenu*, QActionGroup*>& menu)
{
    contextMenu = menu.first;
    actionGroup = menu.second;
}

template<typename SignalType>
void GraphContainer<SignalType>::setTitle(QString titleString, QFont font)
{
    if (!title)
    {
        plotLayout()->insertRow(0);
        title = new QCPTextElement(this, titleString, font);
        plotLayout()->addElement(0, 0, title);
        rescaleAxes();
    }
    else
    {
        title->setText(titleString);
    }
}

template<typename SignalType>
double GraphContainer<SignalType>::getMaxX()
{
    double maxX = -std::numeric_limits<double>::infinity(); // Initialize with the lowest possible value

    // Iterate through all graphs in the QCustomPlot
    for (int i = 0; i < graphCount(); ++i)
    {
        QCPGraph* g = graph(i);
        if (g)
        {
            bool f;
            QCPRange range = g->getKeyRange(f);

                // Update maxX if the current graph's max x is larger
                if (range.upper > maxX)
                    maxX = range.upper;
            }
        }

    return maxX;
}

template<typename SignalType>
bool GraphContainer<SignalType>::isEmpty()
{
    for (int i = 0; i < graphCount(); i++)
    {
        if (!graph(i)->data()->isEmpty())
            return false;
    }
    return true;
}


template<typename SignalType>
void GraphContainer<SignalType>::clearSignals()
{
    for (int i = 0; i < m_Signals.size(); i++)
    {
        SignalType* signal = m_Signals.at(i);
        signal->data()->clear();
        currentLayer()->replot();
    }
}

template class GraphContainer<LoopSignal>;
template class GraphContainer<TimeSignal>;
