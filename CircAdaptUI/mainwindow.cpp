#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include "modelwrapper.h"
#include "settings.h"
#include <QObject>


MainWindow::MainWindow(ModelWrapper& mw, Buffer& buffer, QWidget *parent)
    : QMainWindow(parent)
    , mw(mw)
    , buffer(buffer)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ssGraph->setVisible(false);

    mParamViewDockWidget = new ParamViewDockWidget(this);
    mParamViewDockWidget->setVisible(false);
    QObject::connect(mParamViewDockWidget, &ParamViewDockWidget::paramChanged, &mw, &ModelWrapper::updateParam, Qt::QueuedConnection);

    ui->pvGraph->setup(Settings::instance().PVGraph());
    QObject::connect(ui->graphGrid, &GraphGrid::verticalLineDrawn, ui->pvGraph, &LoopGraph::updateMarker);

    ui->ssGraph->setup(Settings::instance().SSGraph());
    QObject::connect(ui->graphGrid, &GraphGrid::verticalLineDrawn, ui->ssGraph, &LoopGraph::updateMarker);

    ui->valueView->layout()->setContentsMargins(QMargins(0,0,0,5));

    QObject::connect(ui->actionPlay, &QAction::toggled, this, [this](bool isPlay) { emit togglePlay(isPlay); });
    QObject::connect(ui->actionParameter_Settings, &QAction::toggled, mParamViewDockWidget, &QWidget::setVisible);
    QObject::connect(ui->actionStress_strain, &QAction::toggled, this, [this](bool isVisible) { ui->ssGraph->setVisible(isVisible); });
    QObject::connect(ui->actionPressures, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(0, isVisible); });
    QObject::connect(ui->actionVolumes, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(1, isVisible); });
    QObject::connect(ui->actionFlows, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(2, isVisible); });
    QObject::connect(ui->actionStress, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(3, isVisible); });
    QObject::connect(ui->actionStrain, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(4, isVisible); });
    QObject::connect(ui->actionSaturation, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(5, isVisible); });
    QObject::connect(ui->actionM_mode, &QAction::toggled, this, [this](bool isVisible) { ui->graphGrid->setRowVisible(6, isVisible); });
    QObject::connect(ui->actionAutoscale, &QAction::triggered, this, &MainWindow::autoscaleAll);
    QObject::connect(ui->actionSnapshot, SIGNAL(triggered()), this, SLOT(takeSnapshot()));
    QObject::connect(ui->actionReset, &QAction::triggered, this, &MainWindow::resetSlot);
    QObject::connect(ui->actionShow_oxygen, &QAction::triggered, mParamViewDockWidget, &ParamViewDockWidget::showOxygen);
    QObject::connect(&buffer, &Buffer::updateValueView, ui->valueView, &ValueView::updateValues);
    QObject::connect(mParamViewDockWidget, &ParamViewDockWidget::aboutToClose, this, [this]() { ui->actionParameter_Settings->setChecked(false); } );
    QObject::connect(&mw, &ModelWrapper::beat_done, this, [this, &buffer]() { mParamViewDockWidget->updateOxygen(buffer); });
    QObject::connect(this, &MainWindow::updateDone, this, &MainWindow::replot, Qt::QueuedConnection);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete l;
}

void MainWindow::updateGraphs(double timeInterval)
{
    static QQueue<qint64> elapsedTimes;
    static QElapsedTimer overallTimer;
    static qint64 totalElapsed = 0;

    QElapsedTimer timer;
    timer.start();

    ui->graphGrid->updateGraphs(buffer, timeInterval);
    ui->pvGraph->updateGraph(buffer, timeInterval);
    ui->ssGraph->updateGraph(buffer, timeInterval);
    buffer.clear(timeInterval);
    emit updateDone();

    // Calculate the time taken for this call
    qint64 elapsed = timer.elapsed();

    // Update the rolling average every 2 seconds
    if (!overallTimer.isValid())
    {
        overallTimer.start();
    }
    totalElapsed += elapsed;
    elapsedTimes.enqueue(elapsed);

    // Remove times outside the 2-second window
    while (!elapsedTimes.isEmpty() && overallTimer.elapsed() > 2000)
    {
        totalElapsed -= elapsedTimes.dequeue();
        overallTimer.restart();
    }

    // Calculate the average time over the current rolling window
    double averageTime = elapsedTimes.isEmpty() ? 0 : static_cast<double>(totalElapsed) / elapsedTimes.size();
    qDebug() << "Update 2sec avg: " << averageTime << " milliseconds";
}

#include <QElapsedTimer>
#include <QQueue>

void MainWindow::replot()
{
    static QQueue<qint64> elapsedTimes;
    static QElapsedTimer overallTimer;
    static qint64 totalElapsed = 0;

    QElapsedTimer timer;
    timer.start();

    // Perform the replot actions
    ui->graphGrid->replot(GraphGrid::ColType::CURRENT);
    ui->pvGraph->currentLayer()->replot();
    ui->ssGraph->currentLayer()->replot();

    // Calculate the time taken for this call
    qint64 elapsed = timer.elapsed();

    // Update the rolling average every 2 seconds
    if (!overallTimer.isValid())
    {
        overallTimer.start();
    }
    totalElapsed += elapsed;
    elapsedTimes.enqueue(elapsed);

    // Remove times outside the 2-second window
    while (!elapsedTimes.isEmpty() && overallTimer.elapsed() > 2000)
    {
        totalElapsed -= elapsedTimes.dequeue();
        overallTimer.restart();
    }

    // Calculate the average time over the current rolling window
    double averageTime = elapsedTimes.isEmpty() ? 0 : static_cast<double>(totalElapsed) / elapsedTimes.size();
    qDebug() << "Replot 2sec avg: " << averageTime << " milliseconds";
}

void MainWindow::takeSnapshot()
{
    ui->graphGrid->takeSnapshot(buffer);
    ui->pvGraph->displaySnapshot(buffer);
    ui->ssGraph->displaySnapshot(buffer);
}

void MainWindow::displayReference()
{
    ui->graphGrid->displayReference(buffer);
    ui->ssGraph->displayReference(buffer);
    ui->pvGraph->displayReference(buffer);
}

void MainWindow::autoscaleAll()
{
    ui->graphGrid->rescaleAxes();
    ui->graphGrid->replot();
    ui->pvGraph->rescaleAxes();
    ui->pvGraph->replot();
    ui->ssGraph->rescaleAxes();
    ui->ssGraph->replot();

}

void MainWindow::clearSnapshots()
{
    ui->graphGrid->clearSnapshot();
    ui->pvGraph->clearSnapshot();
    ui->ssGraph->clearSnapshot();
}

void MainWindow::resetSlot()
{
    // Pause the GUI update timer
    emit togglePlay(false);

    // Wait for any pending UI updates to complete
    QMetaObject::invokeMethod(this, [this]() {
            // Clear visualization data after updates are done
            ui->graphGrid->clearGraphData();
            ui->pvGraph->clearAllGraphs();
            ui->ssGraph->clearAllGraphs();
            mParamViewDockWidget->resetProperties();

            // Now emit reset signal
            emit resetSignal();
        }, Qt::QueuedConnection);
}
