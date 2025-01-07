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
    m_mainwindow->setWindowState(Qt::WindowFullScreen);
    m_timer = new TimerManager(m_mainwindow, Q_NULLPTR);

    connect(m_mainwindow, &MainWindow::updateDone, &m_mw, &ModelWrapper::run_steps);
    connect(&m_mw, &ModelWrapper::setup_done, m_mainwindow, &MainWindow::displayReference);
    connect(m_mainwindow, &MainWindow::togglePlay, m_timer, &TimerManager::togglePlay);
    connect(m_mainwindow, &MainWindow::resetSignal, this, &CircAdaptUI::reset);


    connect(&m_mw, &ModelWrapper::setup_done, this, [=]() { m_timer->togglePlay(true); });
    m_mw.setup();
    m_mainwindow->show();
    m_mainwindow->autoscaleAll();
}

CircAdaptUI::~CircAdaptUI()
{
    delete m_mainwindow;
    delete m_timer;
}

void CircAdaptUI::reset()
{
    // Reset the model first
    QMetaObject::invokeMethod(&m_mw, "reset", Qt::BlockingQueuedConnection);

    QMetaObject::invokeMethod(this, [this]() {
            // Run steps to refill buffer
            QMetaObject::invokeMethod(&m_mw, "run_steps", Qt::BlockingQueuedConnection);
        }, Qt::QueuedConnection);
}
