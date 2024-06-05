#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject {
    Q_OBJECT
public:
    static Settings& instance() {
        static Settings instance;
        return instance;
    }

    int fps() const {
        return m_settings.value("fps", 60).toInt();
    }

    int buffersize() const {
        return m_settings.value("buffersize", 60).toInt();
    }

    void setFps(int fps) {
        m_settings.setValue("fps", fps);
        emit fpsChanged(fps);
    }

    void buffersize(int buffersize) {
        m_settings.setValue("buffersize", buffersize);
        emit buffersizeChanged(buffersize);
    }

signals:
    void fpsChanged(int fps);
    void buffersizeChanged(int buffersize);

private:
    Settings() : m_settings("YourCompany", "YourApp") {
        m_settings.setValue("fps", 60);
        m_settings.setValue("buffersize", 20);
    }
    ~Settings() {}

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QSettings m_settings;
};


#endif // SETTINGS_H
