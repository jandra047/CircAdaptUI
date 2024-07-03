#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class Settings : public QObject {
    Q_OBJECT
public:
    static Settings& instance() {
        static Settings instance;
        return instance;
    }

    void load(QString filepath);
    QJsonObject GraphGrid() const {  return jsonDoc["GraphGrid"].toObject(); };
    QJsonArray ExportSignals() const {  return jsonDoc["ModelWrapper"]["export_signals"].toArray(); };
    QJsonArray ValueView() const {  return jsonDoc["ValueView"].toArray(); };
    QJsonObject MWSettings() const { return jsonDoc["ModelWrapper"].toObject(); };

    int fps() const {
        return m_settings.value("GUI/framerate", 2).toInt();
    }

    int beatIdx() const {
        return m_settings.value("ModelWrapper/beatIdx", 0).toInt();
    }

    int buffersize() const {
        return m_settings.value("buffersize", 60).toInt();
    }

    double paddingVertical() const {
        return m_settings.value("GUI/paddingVertical", 0.05).toDouble();
    }

    void beatIdxIncrement() {
        m_settings.setValue("ModelWrapper/beatIdx", beatIdx() + 1);
    }

signals:
    void fpsChanged(int fps);
public slots:

    void setFps(int fps) {
        m_settings.setValue("framerate", fps);
        emit fpsChanged(fps);
    }

private:
    Settings() :
        m_settings("CircAdapt", "Andrija") {};
    ~Settings() {};

    void parseJsonObject(const QJsonObject &jsonObj, const QString &prefix = "");
    void setDefaultConfig();
    QJsonDocument jsonDoc{};

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QSettings m_settings;
};


#endif // SETTINGS_H
