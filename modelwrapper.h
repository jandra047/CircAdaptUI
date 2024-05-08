#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H
#include <QVector>
#include <QObject>
#include "Core.hpp"

class ModelWrapper : public QObject, public CAcore::Core {
        Q_OBJECT

public:
    ModelWrapper(QObject *parent = Q_NULLPTR) :
        QObject(parent),
        CAcore::Core(new CAcore::Factory)
    {
        build("VanOsta2022", "forward_euler");
        };

    CAcore::Core* build_model(const char *model, const char *solver);
    void set_model_state();
    QVector<double> get_vec(const char*);

};

#endif // MODELWRAPPER_H
