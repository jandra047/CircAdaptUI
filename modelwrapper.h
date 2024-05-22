#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H
#include <QVector>
#include <QObject>
#include <QThread>
#include "Core.hpp"
#include <buffer.h>

class ModelWrapper : public QObject, public CAcore::Core {

        Q_OBJECT

public:
    ModelWrapper(Buffer& buffer, QMutex& mutex) :
        QObject(),
        CAcore::Core(new CAcore::Factory),
        buffer(buffer),
        mutex(mutex)
    {
        build("VanOsta2022", "forward_euler");
        set_model_state();
        init_SVar();
        m_thread.reset(new QThread);
        moveToThread(m_thread.get());
        m_thread->start();
    };

    ~ModelWrapper()
    {
        QMetaObject::invokeMethod(this, "cleanup");
        m_thread->wait();
    }

    void set_model_state();

private:
    Buffer& buffer;
    QMutex& mutex;
    size_t it = 0;
    int nt;
    double t_export;
    void updateBuffer();
    std::unique_ptr<QThread> m_thread;
public slots:
    void run_single_step();
signals:
    void timestep_done();
private slots:
    void cleanup()
    {
        // delete members...
        m_thread->quit();
    }
};

#endif // MODELWRAPPER_H
