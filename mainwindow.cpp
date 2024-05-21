#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <modelwrapper.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , buffer()
{
    ModelWrapper* mw = new ModelWrapper(buffer);
    ui->setupUi(this);
    connect(timer, &QTimer::timeout, mw, &ModelWrapper::run_single_step);
    connect(buffertimer, &QTimer::timeout, this, &MainWindow::updateGraphs);

    timer->start(0);
    buffertimer->setSingleShot(true);
    buffertimer->start(2000);

    connect(buffertimer, &QTimer::timeout, [&]() {
        buffertimer->start(1000/60);
    });


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
    ui->a->rescaleAxes(true);
    ui->a->replot();
}

void MainWindow::updateGraphs()
{
    ui->a->updateGraphs(buffer);
    buffer.take("t", 0.015);
}
