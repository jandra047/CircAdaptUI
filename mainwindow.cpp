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

    LoopSignal* sig = new LoopSignal(ui->pvGraph->xAxis, ui->pvGraph->yAxis, "pLv", "VLv");
    ui->pvGraph->addSignal(sig);

    connect(this, &MainWindow::updateDone, mw, &ModelWrapper::run_steps);
    connect(buffertimer, &QTimer::timeout, this, &MainWindow::updateGraphs);

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
    delete mw;
}

void MainWindow::on_actionPlay_triggered()
{
    if (timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start();
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
}

void MainWindow::updateGraphs()
{
    ui->graphGrid->updateGraphs(buffer);
    ui->pvGraph->updateGraph(buffer);
    buffer.clear(1000/((double)Settings::instance().fps() * 1000));
    emit updateDone();
}
