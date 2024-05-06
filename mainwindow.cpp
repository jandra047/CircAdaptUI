#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <modelwrapper.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // setStyleSheet("background-color: #aaaaaa");
    connect(timer, &QTimer::timeout, ui->signalGraph, &SignalGraph::updateGraph);
    connect(timer, &QTimer::timeout, ui->pvGraph, &PVLoopGraph::updateGraph);
    connect(ui->actionPlay, SIGNAL(ui->actionPlay->triggered), this, SLOT(drawToggle));



    ui->signalGraph->createSignals(2);
    ui->pvGraph->createSignals(2);
    // ui->pvGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    // ui->pvGraph->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->pvGraph->xAxis->setRange(0, 200);
    ui->pvGraph->yAxis->setRange(0, 200);
    QList<TimeSignal* > ss = ui->signalGraph->mSignals;
    QList<LoopSignal* > ss2 = ui->pvGraph->mSignals;
    ModelWrapper mw;
    mw.set_model_state();
    // mw.run_stable(true);
    mw.run_single_beat();
    auto const t = mw.get_vec("Solver.t");
    auto VLv = mw.get_vec("Model.Peri.TriSeg.cLv.V");
    auto VRv = mw.get_vec("Model.Peri.TriSeg.cRv.V");
    auto pLv = mw.get_vec("Model.Peri.TriSeg.cLv.p");
    auto pRv = mw.get_vec("Model.Peri.TriSeg.cRv.p");
    for (int i = 0; i < VLv.size(); i++)
    {
        VLv[i] *= 1e6;
        VRv[i] *= 1e6;
        pLv[i] /= 133;
        pRv[i] /= 133;
    }


    ss[0]->setTData(t);
    ss[0]->setYData(pLv);
    ss[1]->setTData(t);
    ss[1]->setYData(pRv);
    ss2[0]->setXData(VLv);
    ss2[0]->setYData(pLv);
    ss2[0]->setTData(t);
    // ss2[0]->addData(t, VLv, pLv);
    // ss2[0]->data()->remove(0.3, 0.7);
    // ss2[0]->addData(0.5, quiet_nan, quiet_nan);
    // ss2[0]->layer()->replot();
    ss2[1]->setXData(VRv);
    ss2[1]->setYData(pRv);
    ss2[1]->setTData(t);
    // ss2[1]->setPen(QPen(Qt::red));

    timer->start(10);


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
