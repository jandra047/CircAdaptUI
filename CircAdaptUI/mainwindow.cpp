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
    l = new QLabel(ui->graphGrid);

    mParamViewDockWidget = new ParamViewDockWidget(this);
    mParamViewDockWidget->setVisible(false);
    QObject::connect(mParamViewDockWidget, &ParamViewDockWidget::paramChanged, &mw, &ModelWrapper::updateParam, Qt::QueuedConnection);

    LoopSignal* sig = new LoopSignal(ui->pvGraph->xAxis, ui->pvGraph->yAxis, "Left ventricle", "pLv", "VLv", QColor(227, 26, 28));
    LoopSignal* sig2 = new LoopSignal(ui->pvGraph->xAxis, ui->pvGraph->yAxis, "Right ventricle", "pRv", "VRv", QColor(31, 120, 180));
    ui->pvGraph->addSignal(sig);
    ui->pvGraph->addSignal(sig2);
    ui->pvGraph->setTitle("Pressure-volume loops", QFont("Liberation Sans", 12, QFont::Bold));
    auto pvMenu = ui->pvGraph->buildMenu(ui->pvGraph);
    ui->pvGraph->setContextMenu(pvMenu);
    QObject::connect(pvMenu.second, &QActionGroup::triggered, this, [=](QAction* action) { ui->pvGraph->showSignal(action); });
    QObject::connect(ui->graphGrid, &GraphGrid::verticalLineDrawn, ui->pvGraph, &LoopGraph::updateMarker);

    LoopSignal* sig3 = new LoopSignal(ui->ssGraph->xAxis, ui->ssGraph->yAxis, "Left ventricular free wall", "Sf_Lv", "Ef_Lv", QColor(227, 26, 28));
    LoopSignal* sig4 = new LoopSignal(ui->ssGraph->xAxis, ui->ssGraph->yAxis, "Septal wall", "Sf_Sv", "Ef_Sv", QColor(0,0,0));
    LoopSignal* sig5 = new LoopSignal(ui->ssGraph->xAxis, ui->ssGraph->yAxis, "Right ventricular free wall", "Sf_Rv", "Ef_Rv", QColor(31, 120, 180));
    ui->ssGraph->addSignal(sig3);
    ui->ssGraph->addSignal(sig4);
    ui->ssGraph->addSignal(sig5);
    ui->ssGraph->setTitle("Stress-strain loops", QFont("Liberation Sans", 12, QFont::Bold));
    auto ssMenu = ui->ssGraph->buildMenu(ui->ssGraph);
    ui->ssGraph->setContextMenu(ssMenu);
    QObject::connect(ssMenu.second, &QActionGroup::triggered, this, [=](QAction* action) { ui->ssGraph->showSignal(action); });
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
    QObject::connect(&buffer, &Buffer::updateValueView, ui->valueView, &ValueView::updateValues);
    QObject::connect(mParamViewDockWidget, &ParamViewDockWidget::aboutToClose, this, [this]() { ui->actionParameter_Settings->setChecked(false); } );
}


MainWindow::~MainWindow()
{
    delete ui;
    delete l;
}

void MainWindow::updateGraphs()
{
    ui->graphGrid->updateGraphs(buffer);
    ui->pvGraph->updateGraph(buffer);
    ui->ssGraph->updateGraph(buffer);
    buffer.clear(1/(double)Settings::instance().fps());
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

