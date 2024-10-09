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
    QObject::connect(ui->actionAutoscale, &QAction::triggered, this, &MainWindow::autoscaleAll);
    QObject::connect(ui->actionSnapshot, SIGNAL(triggered()), this, SLOT(takeSnapshot()));
    QObject::connect(ui->actionReset, &QAction::triggered, this, &MainWindow::clearSnapshots);
    QObject::connect(&buffer, &Buffer::updateValueView, ui->valueView, &ValueView::updateValues);
    QObject::connect(mParamViewDockWidget, &ParamViewDockWidget::aboutToClose, this, [this]() { ui->actionParameter_Settings->setChecked(false); } );
}


MainWindow::~MainWindow()
{
    delete ui;
    delete l;
}

void MainWindow::updateGraphs(double timeInterval)
{
    ui->graphGrid->updateGraphs(buffer, timeInterval);
    ui->pvGraph->updateGraph(buffer, timeInterval);
    ui->ssGraph->updateGraph(buffer, timeInterval);
    buffer.clear(timeInterval);
    emit updateDone();
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
    ui->graphGrid->removeSnapshot();
    ui->pvGraph->removeSnapshot();
    ui->ssGraph->removeSnapshot();
}

