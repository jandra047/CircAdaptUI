#include "circadaptui.h"
#include "modelwrapper.h"
#include "settings.h"

CircAdaptUI::CircAdaptUI(int &argc, char **argv):
    QApplication(argc, argv),
    m_mw(ModelWrapper(m_buffer))
{
    Settings::instance().load(qApp->applicationDirPath().append("/config.json"));
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    m_mainwindow = new MainWindow(m_mw, m_buffer);

    connect(m_mainwindow, &MainWindow::updateDone, &m_mw, &ModelWrapper::run_steps);
    connect(&m_mw, &ModelWrapper::setup_done, m_mainwindow, &MainWindow::displayReference);
    connect(m_timer, &QTimer::timeout, m_mainwindow, &MainWindow::updateGraphs);
    connect(m_timer, &QTimer::timeout, m_mainwindow, &MainWindow::updateBufferLenText);
    connect(m_mainwindow, &MainWindow::togglePlay, this, &CircAdaptUI::togglePlay);

    m_mw.setup();
    m_mainwindow->show();
    m_mainwindow->autoscaleAll();
    m_timer->start(1000/(double)Settings::instance().fps());
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
