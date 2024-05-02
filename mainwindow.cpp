#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <QTime>
#define PI 3.14159265359
#include <modelwrapper.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, ui->graph, &GraphContainer::updateGraph);


    ui->graph->createSignals(2);
    QList<Signal* > ss = ui->graph->mSignals;
    ModelWrapper mw;
    mw.set_model_state();
    // mw.run_stable(true);
    mw.run_single_beat();
    auto const t = mw.get_vec("Solver.t");
    auto VLv = mw.get_vec("Model.Peri.TriSeg.cLv.V");
    auto VRv = mw.get_vec("Model.Peri.TriSeg.cRv.V");
    for (int i = 0; i < VLv.size(); i++)
    {
        VLv[i] *= 1e6;
        VRv[i] *= 1e6;
    }


    ss[0]->setXData(t);
    ss[0]->setYData(VLv);
    ss[1]->setXData(t);
    ss[1]->setYData(VRv);

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
