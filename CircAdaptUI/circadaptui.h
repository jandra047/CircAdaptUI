#ifndef CIRCADAPTUI_H
#define CIRCADAPTUI_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread() {};
    MyThread(MainWindow* mw, QObject* parent = Q_NULLPTR):
        QThread(parent),
        m_mainwindow(mw)
    {
        connect(timer, &QTimer::timeout, this, &MyThread::realtimeSlot);
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
};

class CircAdaptUI : public QApplication
{
    Q_OBJECT
public:
    CircAdaptUI(int &argc, char **argv);
    ~CircAdaptUI();

private:
    MainWindow* m_mainwindow = Q_NULLPTR;
    QTimer *m_timer = new QTimer(this);
    Buffer m_buffer{};
    ModelWrapper m_mw;

    MyThread* m_thread;

    double fps;

private slots:
    void togglePlay(bool isOn);
    void realtimeSlot();
    void reset();
};

#endif // CIRCADAPTUI_H
