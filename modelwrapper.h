#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H
#include <QVector>
#include <QObject>
#include "Core.hpp"
#include <buffer.h>

class ModelWrapper : public QObject, public CAcore::Core {
        Q_OBJECT

public:
    ModelWrapper(Buffer& buffer, QObject *parent = Q_NULLPTR) :
        QObject(parent),
        CAcore::Core(new CAcore::Factory),
        buffer(buffer)
    {
        build("VanOsta2022", "forward_euler");
        set_model_state();
        init_SVar();
    };

    void set_model_state();

private:
    Buffer& buffer;
    size_t it = 0;
    int nt;
    double t_export;
    void updateBuffer();
public slots:
    void run_single_step();
signals:
    void timestep_done();
};

#endif // MODELWRAPPER_H
