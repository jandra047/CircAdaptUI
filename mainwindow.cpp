#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTime>
#include <modelwrapper.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , buffer()
    , mw(buffer, this)
{
    ui->setupUi(this);
    // setStyleSheet("background-color: #aaaaaa");
    connect(timer, &QTimer::timeout, &mw, &ModelWrapper::run_single_step);
    // connect(&mw, &ModelWrapper::timestep_done, this, &MainWindow::updateSigGraph);
    // connect(&mw, &ModelWrapper::timestep_done, this, &MainWindow::updatePVGraph);
    // connect(&mw, &ModelWrapper::timestep_done, ui->ssGraph, &PVLoopGraph::updateGraph);


    ui->splitter->addWidget(a);
    connect(buffertimer, &QTimer::timeout, this, &MainWindow::updateGraphs);

    timer->start(0);
    buffertimer->setSingleShot(true);
    buffertimer->start(2000); // 5000 milliseconds = 5 seconds

    // Connect the timer's timeout signal to a lambda function
    connect(buffertimer, &QTimer::timeout, [&]() {

        // Start the timer with a 100 ms interval
        buffertimer->start(1000/60);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
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

// void MainWindow::on_actionAutoscale_triggered()
// {
//     ui->signalGraph->rescaleAxes(true);
//     ui->signalGraph->replot();
//     ui->ssGraph->rescaleAxes(true);
//     ui->ssGraph->replot();
//     ui->pvGraph->rescaleAxes(true);
//     ui->pvGraph->replot();
// }

void MainWindow::updateGraphs()
{
    a->updateGraphs(buffer);
    buffer.take("t", 0.015);
}
