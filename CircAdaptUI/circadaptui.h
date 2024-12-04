#ifndef CIRCADAPTUI_H
#define CIRCADAPTUI_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include <QtConcurrent/QtConcurrent>
#include "settings.h"
#include <sys/time.h>

// class TimerThread : public QThread
// {
//     Q_OBJECT
// public:
//     TimerThread() {};
//     ~TimerThread()
//     {
//         timer->stop();
//         delete timer;
//         exit();
//         wait();
//         deleteLater();

//     }
//     TimerThread(MainWindow* mw, QObject* parent = Q_NULLPTR):
//         QThread(parent),
//         m_mainwindow(mw)
//     {
//         fps = Settings::instance().fps();
//         connect(timer, &QTimer::timeout, this, &TimerThread::realtimeSlot);
//         start();
//     };
//     QTime timeStart = QTime::currentTime();
//     double timeLastUpdate = 0;
//     QTimer* timer = new QTimer(this);
//     MainWindow* m_mainwindow;
//     double fps = 60;
// public slots:
//     void realtimeSlot()
//     {
//         static double trueFPS = 1000;
//         double timeElapsed = timeStart.msecsTo(QTime::currentTime())/1000.0;
//         static double timeLastFps;
//         static int frameCount;

//         if (timeElapsed - timeLastUpdate > 1/fps)
//         {
//         double currfps = 1/(timeElapsed - timeLastUpdate);
//         QFuture<void> future = QtConcurrent::run(
//             &MainWindow::updateGraphs,
//             m_mainwindow,
//             (fps < trueFPS) ? 1/currfps : 1/trueFPS);
//         timeLastUpdate = timeElapsed;
//         }
//         ++frameCount;

//         if (timeElapsed - timeLastFps > 0.01)
//         {
//         trueFPS = frameCount/(timeElapsed-timeLastFps);
//         timeLastFps = timeElapsed;
//         frameCount = 0;
//         }

//     }

//     void togglePlay(bool isPlay)
//     {
//         if (!isPlay)
//         {
//             timer->stop();
//         }
//         else
//         {
//             timeStart = QTime::currentTime();
//             timeLastUpdate = 0;
//             timer->start(0);
//         }
//     }

// };
class TimerThread : public QThread
{
    Q_OBJECT
public:
    TimerThread() {};
    ~TimerThread()
    {
        m_running = false;
        exit();
        wait();
        deleteLater();
    }

    TimerThread(MainWindow* mw, QObject* parent = Q_NULLPTR):
        QThread(parent),
        m_mainwindow(mw),
        m_running(false)
    {
        fps = Settings::instance().fps();
    };

    MainWindow* m_mainwindow;
    double fps = 60;
    bool m_running;

#ifdef WIN32
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_lastTime;
#else
    struct timeval m_lastTime;
#endif

protected:
    void run() override {
#ifdef WIN32
        // Get the timer frequency on Windows
        QueryPerformanceFrequency(&m_frequency);
        // Get initial time
        QueryPerformanceCounter(&m_lastTime);
#else \
    // Get initial time on Unix systems
        gettimeofday(&m_lastTime, 0);
#endif
        m_running = true;

        while (m_running) {
#ifdef WIN32
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);
            // Calculate elapsed time in seconds
            double elapsed = double(currentTime.QuadPart - m_lastTime.QuadPart) /
                             double(m_frequency.QuadPart);
#else
            struct timeval currentTime;
            gettimeofday(&currentTime, 0);
            // Calculate elapsed time in seconds
            double elapsed = (currentTime.tv_sec - m_lastTime.tv_sec) +
                             (currentTime.tv_usec - m_lastTime.tv_usec) * 1e-6;
#endif

            static double timeLastFps = 0;
            static int frameCount = 0;
            static double trueFPS = 1000;

            if (elapsed >= 1.0/fps) {
                double currfps = 1.0/elapsed;
                QFuture<void> future = QtConcurrent::run(
                    &MainWindow::updateGraphs,
                    m_mainwindow,
                    (fps < trueFPS) ? 1/currfps : 1/trueFPS);

                m_lastTime = currentTime;
                frameCount++;

                if (elapsed - timeLastFps > 0.01) {
                    trueFPS = frameCount/(elapsed-timeLastFps);
                    timeLastFps = elapsed;
                    frameCount = 0;
                }
            }

            // Small sleep to prevent excessive CPU usage
            QThread::usleep(100);
        }
    }

public slots:
    void togglePlay(bool isPlay)
    {
        if (!isPlay)
        {
            m_running = false;
        }
        else
        {
            if (!isRunning()) {
                m_running = true;
                start();
            }
        }
    }
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

    TimerThread* m_thread;

private slots:
    void reset();
};

#endif // CIRCADAPTUI_H
