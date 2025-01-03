#ifndef MODELWRAPPER_H
#define MODELWRAPPER_H
#include <QVector>
#include <QObject>
#include <QThread>
#include "Core.hpp"
#include "buffer.h"
#include <QJsonObject>
#include "datacontainer.h"

/*!
 * \brief A class which wraps the Core class of CircAdapt
 *
 * ModelWrapper is used for manipulating the simulation engine
 * (changing model parameters, running simulation steps),
 * appending the data to the buffer. It lives in its separate
 * thread.
 */
class ModelWrapper : public QObject, public CAcore::Core {

        Q_OBJECT

public:
     /*!
     * \brief Builds and initializes the CircAdapt model and moves
     * to a separate thread.
     * \param buffer A buffer object to fill with simulation data
     */
    ModelWrapper(Buffer& buffer) :
        QObject(),
        CAcore::Core(new CAcore::Factory),
        buffer(buffer)
    {
    };

    ~ModelWrapper()
    {
        QMetaObject::invokeMethod(this, "cleanup");
        m_thread->wait();
    }

    QThread* get_thread() { return m_thread.get(); };
    void setup();
    void buildModel();
    void setReferenceParameters();
    Q_INVOKABLE void reset();

private:

    /*!
     * \brief Reference to the buffer
     */
    Buffer& buffer;

    /*!
     * \brief Iteration step of the solver
     */
    size_t it = -1;

    /*!
     * \brief Number of iterations in one beat with current solver settings
     */
    int nt;

    /*!
     * \brief Time point which needs to be calculated by the solver
     */
    double t_export;

    /*!
     * \brief Appends simulated data to \ref Buffer
     */
    void updateBuffer();

    /*!
     * \brief Holds a pointer to the thread which \ref ModelWrapper object lives in
     */
    std::unique_ptr<QThread> m_thread;

    QVector<DataContainer*> mModelSignals;

    QMap<QString, DataContainer*> mModelParameters;

    void setupSignals();
    void setupAdditionalSignals();
    void setupParameters();
    void run_beats(int N_beats);

    bool beatDone {false};

public slots:
    /*!
     * \brief Runs a number of steps until \ref Buffer length reaches value specified at \ref Settings
     */
    void run_steps();

    /*!
     * \brief Runs single solver step
     */
    void run_single_step();

    void updateParam(const QString& path, const QVariant& value);

signals:

    /*!
     * \brief Emits a signal after \ref ModelWrapper is done calculating one timestep
     */
    void timestep_done();

    /*!
     * \brief Emits a signal after whole beat is done
     */
    void beat_done();

    void setup_done();

private slots:
    void cleanup()
    {
        delete factory;
        m_thread->quit();
    }
};

#endif // MODELWRAPPER_H
