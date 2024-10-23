#include "circadaptui.h"
#include "modelwrapper.h"
#include "settings.h"
#include <QStyleFactory>

CircAdaptUI::CircAdaptUI(int &argc, char **argv):
    QApplication(argc, argv),
    m_mw(ModelWrapper(m_buffer))
{
    setStyle(QStyleFactory::create("Fusion"));

    Settings::instance().load(qApp->applicationDirPath().append("/config.json"));
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    m_mainwindow = new MainWindow(m_mw, m_buffer);
    m_thread = new MyThread(m_mainwindow, this);

    connect(m_mainwindow, &MainWindow::updateDone, &m_mw, &ModelWrapper::run_steps);
    connect(&m_mw, &ModelWrapper::setup_done, m_mainwindow, &MainWindow::displayReference);
    // connect(m_timer, &QTimer::timeout, this, &CircAdaptUI::realtimeSlot);
    connect(m_mainwindow, &MainWindow::togglePlay, this, &CircAdaptUI::togglePlay);
    connect(m_mainwindow, &MainWindow::resetSignal, this, &CircAdaptUI::reset);

    fps = Settings::instance().fps();

    m_thread->start();
    connect(&m_mw, &ModelWrapper::setup_done, this, [=]() { m_thread->timer->start(0); });
    m_mw.setup();
    m_mainwindow->show();
    m_mainwindow->autoscaleAll();

    // m_thread.timer->start(0);

}

void CircAdaptUI::realtimeSlot()
{
    static QTime timeStart = QTime::currentTime();
    static double trueFPS = 1000;
    double timeElapsed = timeStart.msecsTo(QTime::currentTime())/1000.0;
    static double timeLastUpdate = 0;
    static double timeLastFps;
    static int frameCount;

    if (timeElapsed - timeLastUpdate > 1/fps)
    {
        double currfps = 1/(timeElapsed - timeLastUpdate);
        m_mainwindow->updateGraphs(
            (fps < trueFPS) ? 1/currfps : 1/trueFPS
            );
        timeLastUpdate = timeElapsed;
    }
    ++frameCount;

    if (timeElapsed - timeLastFps > 0.01)
    {
        trueFPS = frameCount/(timeElapsed-timeLastFps);
        timeLastFps = timeElapsed;
        frameCount = 0;
    }

}

CircAdaptUI::~CircAdaptUI()
{
    delete m_mainwindow;
    delete m_timer;
}

void CircAdaptUI::togglePlay(bool isOn)
{
    if (isOn)
    {
        m_timer->start();
    }
    else
    {
        m_timer->stop();
    }
}

void CircAdaptUI::reset()
{
    m_timer->stop();
    QMetaObject::invokeMethod(&m_mw, "reset");;

}
