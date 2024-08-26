#include "graphcontainer.h"
#include "CircAdaptUI/Signals/loopsignal.h"
#include "CircAdaptUI/Signals/timesignal.h"

template<typename SignalType>
GraphContainer<SignalType>::GraphContainer(QWidget* parent) :
    QCustomPlot(parent),
    contextMenu(Q_NULLPTR),
    actionGroup(Q_NULLPTR),
    m_lineMarker(LineMarker(this)),
    title(Q_NULLPTR)
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
    xAxis->ticker()->setTickCount(5);
    xAxis->setTickLabelFont(tickLabelFont);
    xAxis->setLabelFont(labelFont);
    xAxis->grid()->setPen(QPen(QColor(0xcccccc), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    yAxis->ticker()->setTickCount(5);
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
GraphContainer<SignalType>::~GraphContainer()
{
    while (m_Signals.count())
    {
        delete m_Signals.takeLast();
    }

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
    }
    else
    {
        title->setText(titleString);
    }
}
template class GraphContainer<LoopSignal>;
template class GraphContainer<TimeSignal>;
