#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <QTime>
#define PI 3.14159265359

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    // timer->setInterval(100);
    connect(timer, &QTimer::timeout, ui->graph, &GraphContainer::updateGraph);


    ui->graph->createSignals(20);
    QVector<double> x,y;
    for (int i = 0; i < 20; i++)
    {
        x = linspace(0, 2 * PI, 426);
        y = sine(x, i);
        ui->graph->mSignals[i]->setXData(x);
        ui->graph->mSignals[i]->setYData(y);


    }

    timer->start(10);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<double> MainWindow::sine(QVector<double> &x, double phase)
{
    QVector<double> y(x.size());
    for (int i = 0; i < x.size(); i++)
    {
        y[i] = sin(x[i] - phase);
    }
    return y;
}

QVector<double> MainWindow::linspace(double x0, double x1, int N_samples)
{
    double delta = (x1 - x0)/(N_samples - 1);
    QVector<double> x;

    for (int i = 0; i < N_samples - 1; i++)
    {
        x.push_back(x0 + i * delta);
    }

    x.push_back(x1);
    return x;
}
