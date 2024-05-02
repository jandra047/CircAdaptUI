#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H
#import <QVector>
#import "Core.hpp"

class ModelWrapper : public CAcore::Core {

public:
    ModelWrapper() : CAcore::Core(new CAcore::Factory) {
        build("VanOsta2022", "forward_euler");
        };

    CAcore::Core* build_model(const char *model, const char *solver);
    void set_model_state();
    QVector<double> get_vec(const char*);

};

#endif // MODELWRAPPER_H
