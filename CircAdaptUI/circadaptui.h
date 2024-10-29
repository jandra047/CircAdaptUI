#ifndef CIRCADAPTUI_H
#define CIRCADAPTUI_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include <QtConcurrent/QtConcurrent>
#include "settings.h"

class TimerThread : public QThread
{
    Q_OBJECT
public:
    TimerThread() {};
    TimerThread(MainWindow* mw, QObject* parent = Q_NULLPTR):
        QThread(parent),
        m_mainwindow(mw)
    {
        fps = Settings::instance().fps();
        connect(timer, &QTimer::timeout, this, &TimerThread::realtimeSlot);
        start();
    };
    QTimer* timer = new QTimer(this);
    MainWindow* m_mainwindow;
    double fps = 60;
public slots:
    void realtimeSlot()
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
        QFuture<void> future = QtConcurrent::run(
            &MainWindow::updateGraphs,
            m_mainwindow,
            (fps < trueFPS) ? 1/currfps : 1/trueFPS);
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
    void togglePlay(bool isOn);
    void reset();
};

#endif // CIRCADAPTUI_H
