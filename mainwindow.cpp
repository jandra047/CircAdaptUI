#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <modelwrapper.h>
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , buffer()
{
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    ModelWrapper* mw = new ModelWrapper(buffer);
    ui->setupUi(this);
    ui->ssGraph->setVisible(false);
    l = new QLabel(ui->graphGrid);

    LoopSignal* sig = new LoopSignal(ui->pvGraph->xAxis, ui->pvGraph->yAxis, "pLv", "VLv", QColor(227, 26, 28));
    LoopSignal* sig2 = new LoopSignal(ui->pvGraph->xAxis, ui->pvGraph->yAxis, "pRv", "VRv", QColor(31, 120, 180));
    ui->pvGraph->addSignal(sig);
    ui->pvGraph->addSignal(sig2);
    LoopSignal* sig3 = new LoopSignal(ui->ssGraph->xAxis, ui->ssGraph->yAxis, "Sf_Lv", "Ef_Lv", QColor(227, 26, 28));
    LoopSignal* sig4 = new LoopSignal(ui->ssGraph->xAxis, ui->ssGraph->yAxis, "Sf_Sv", "Ef_Sv", QColor(0,0,0));
    LoopSignal* sig5 = new LoopSignal(ui->ssGraph->xAxis, ui->ssGraph->yAxis, "Sf_Rv", "Ef_Rv", QColor(31, 120, 180));
    ui->ssGraph->addSignal(sig3);
    ui->ssGraph->addSignal(sig4);
    ui->ssGraph->addSignal(sig5);
    QSlider* s = new QSlider(Qt::Horizontal, ui->widget);
    s->setMinimum(50);
    s->setMaximum(150);
    s->setSingleStep(10);
    s->setSliderPosition(100);
    s->setTickPosition(QSlider::TicksBelow);
    s->setTickInterval(10);


    connect(this, &MainWindow::updateDone, mw, &ModelWrapper::run_steps);
    connect(buffertimer, &QTimer::timeout, this, &MainWindow::updateGraphs);
    connect(s, &QSlider::valueChanged, mw, &ModelWrapper::changeParam, Qt::QueuedConnection);

    buffertimer->setSingleShot(true);
    buffertimer->start(2000);

    connect(buffertimer, &QTimer::timeout, [&]() {
        buffertimer->start(1000/(double)Settings::instance().fps());
    });

    connect(buffertimer, &QTimer::timeout, this, &MainWindow::changetext);

}


MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete buffertimer;
    delete mw;
}

void MainWindow::on_actionPlay_triggered()
{
    if (buffertimer->isActive())
    {
        buffertimer->stop();
    }
    else
    {
        buffertimer->start();
    }
}

void MainWindow::on_actionStress_strain_toggled(bool isVisible)
{
    ui->ssGraph->setVisible(isVisible);
}

void MainWindow::on_actionAutoscale_triggered()
{
    ui->graphGrid->rescaleAxes(true);
    ui->graphGrid->replot();
    ui->pvGraph->rescaleAxes(true);
    ui->pvGraph->replot();
    ui->ssGraph->rescaleAxes(true);
    ui->ssGraph->replot();
}

void MainWindow::updateGraphs()
{
    ui->graphGrid->updateGraphs(buffer);
    ui->pvGraph->updateGraph(buffer);
    ui->ssGraph->updateGraph(buffer);
    buffer.clear(1000/((double)Settings::instance().fps() * 1000));
    emit updateDone();
}
