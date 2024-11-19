#include "circadaptui.h"
#include "modelwrapper.h"
#include <QStyleFactory>

CircAdaptUI::CircAdaptUI(int &argc, char **argv):
    QApplication(argc, argv),
    m_mw(ModelWrapper(m_buffer))
{
    setStyle(QStyleFactory::create("Fusion"));

    Settings::instance().load(qApp->applicationDirPath().append("/config.json"));
    QThread::currentThread()->setPriority(QThread::HighestPriority);
    m_mainwindow = new MainWindow(m_mw, m_buffer);
    m_thread = new TimerThread(m_mainwindow, this);

    connect(m_mainwindow, &MainWindow::updateDone, &m_mw, &ModelWrapper::run_steps);
    connect(&m_mw, &ModelWrapper::setup_done, m_mainwindow, &MainWindow::displayReference);
    connect(m_mainwindow, &MainWindow::togglePlay, this, &CircAdaptUI::togglePlay);
    connect(m_mainwindow, &MainWindow::resetSignal, this, &CircAdaptUI::reset);


    connect(&m_mw, &ModelWrapper::setup_done, this, [=]() { m_thread->timer->start(0); });
    m_mw.setup();
    m_mainwindow->show();
    m_mainwindow->autoscaleAll();
}

CircAdaptUI::~CircAdaptUI()
{
    delete m_mainwindow;
    delete m_thread;
}

void CircAdaptUI::togglePlay(bool isOn)
{
    if (isOn)
    {
        m_thread->timer->start();
    }
    else
    {
        m_thread->timer->stop();
    }
}

void CircAdaptUI::reset()
{
    // Reset the model first
    QMetaObject::invokeMethod(&m_mw, "reset", Qt::BlockingQueuedConnection);

    // After model reset, clear and reinitialize buffer
    QMetaObject::invokeMethod(this, [this]() {
            m_buffer.clear();
            // Run steps to refill buffer
            QMetaObject::invokeMethod(&m_mw, "run_steps", Qt::BlockingQueuedConnection);
        }, Qt::QueuedConnection);
}
