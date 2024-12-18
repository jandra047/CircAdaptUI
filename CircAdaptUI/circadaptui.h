#ifndef CIRCADAPTUI_H
#define CIRCADAPTUI_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include <QtConcurrent/QtConcurrent>
#include "settings.h"

class TimerManager : public QObject
{
    Q_OBJECT
public:
    TimerManager(MainWindow* mw, QObject* parent = nullptr):
        QObject(parent),
        m_mainwindow(mw),
        m_timer(new QTimer(Q_NULLPTR))
    {
        fps = Settings::instance().fps();

        // Move the timer to a separate thread for better timing accuracy
        m_timerThread = new QThread(this);
        // this->moveToThread(m_timerThread);
        // m_timer->moveToThread(m_timerThread);

        connect(m_timer, &QTimer::timeout, this, &TimerManager::realtimeSlot);
        connect(m_timerThread, &QThread::finished, m_timer, &QTimer::stop);
        connect(m_timerThread, &QThread::finished, m_timerThread, &QThread::deleteLater);

        m_timerThread->start(QThread::HighPriority);
    }

    ~TimerManager()
    {
        if (m_timerThread) {
            m_timer->stop();
            m_timerThread->quit();
            m_timerThread->wait();
        }
    }

public slots:
    void realtimeSlot()
    {
        static double trueFPS = 1000;
        double timeElapsed = m_timeStart.msecsTo(QTime::currentTime())/1000.0;
        static double timeLastFps;
        static int frameCount;

        if (timeElapsed - m_timeLastUpdate >= 1/fps)
        {
            double currfps = 1/(timeElapsed - m_timeLastUpdate);
            QFuture<void> future = QtConcurrent::run(
                &MainWindow::updateGraphs,
                m_mainwindow,
                (fps < trueFPS) ? 1/currfps : 1/trueFPS);
            m_timeLastUpdate = timeElapsed;
        }
        ++frameCount;

        if (timeElapsed - timeLastFps > 0.01)
        {
            trueFPS = frameCount/(timeElapsed-timeLastFps);
            timeLastFps = timeElapsed;
            frameCount = 0;
        }
    }

    void togglePlay(bool isPlay)
    {
        if (!isPlay)
        {
            m_timer->stop();
        }
        else
        {
            m_timeStart = QTime::currentTime();
            m_timeLastUpdate = 0;
            m_timer->start(0);
        }
    }

private:
    MainWindow* m_mainwindow;
    QTimer* m_timer;
    QThread* m_timerThread;
    QTime m_timeStart = QTime::currentTime();
    double m_timeLastUpdate = 0;
    double fps = 60;
};

class CircAdaptUI : public QApplication
{
    Q_OBJECT
public:
    CircAdaptUI(int &argc, char **argv);
    ~CircAdaptUI();

private:
    MainWindow* m_mainwindow = Q_NULLPTR;
    Buffer m_buffer{};
    ModelWrapper m_mw;

    TimerManager* m_timer;

private slots:
    void reset();
};

#endif // CIRCADAPTUI_H
