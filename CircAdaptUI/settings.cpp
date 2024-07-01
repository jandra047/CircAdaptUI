#include "settings.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

// Settings::Settings():
//     m_settings("settings.ini", QSettings::IniFormat)
// {
//     QFile configFile("config.json");
//     if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QByteArray jsonData = configFile.readAll();
//         QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
//         qDebug() << jsonDoc["ModelWrapper"]["solver"].toString();
//         m_settings.setValue("framerate", jsonDoc["GUI"]["framerate"].toInt());
//     }

// }

void Settings::load(QString filepath)
{
    QFile configFile(filepath);
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray jsonData = configFile.readAll();
        jsonDoc = QJsonDocument::fromJson(jsonData);
        parseJsonObject(jsonDoc.object());
    }
    else
    {
        setDefaultConfig();
    }
}

void Settings::parseJsonObject(const QJsonObject &jsonObj, const QString &prefix) {
    // for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
    //     QString key = it.key();
    //     QJsonValue value = it.value();
    //     QString fullKey = prefix.isEmpty() ? key : prefix + "/" + key;

    //     if (value.isObject()) {
    //         parseJsonObject(value.toObject(),  fullKey);
    //     } else if (value.isArray()) {
    //         const QJsonArray& array = value.toArray();
    //         for (int i = 0; i < array.size(); ++i) {
    //             QString arrayKey = fullKey + "/" + QString::number(i);
    //             if (array[i].isObject()) {
    //                 parseJsonObject(array[i].toObject(), arrayKey);
    //             } else {
    //                 m_settings.setValue(arrayKey, array[i].toVariant());
    //             }
    //         }
    //     } else {
    //         m_settings.setValue(fullKey, value.toVariant());
    //     }
    // }

    ///////////// V2
    // for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
    //     QString key = parentKey.isEmpty() ? it.key() : parentKey + "/" + it.key();
    //     if (it->isObject()) {
    //         // Recursively parse the nested JSON object
    //         parseJsonObject(it->toObject(), key);
    //     } else {
    //         // Add the key-value pair to QSettings
    //         m_settings.setValue(key, it.value().toVariant());
    //     }
    // }
    /////////////////

    //////////// V3
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        QString key = prefix.isEmpty() ? it.key() : prefix + "/" + it.key();
        QJsonValue value = it.value();

        switch (value.type()) {
            case QJsonValue::Bool:
                m_settings.setValue(key, value.toBool());
                break;
            case QJsonValue::Double:
                m_settings.setValue(key, value.toDouble());
                break;
            case QJsonValue::String:
                m_settings.setValue(key, value.toString());
                break;
            case QJsonValue::Array: {
                QJsonArray jsonArray = value.toArray();
                m_settings.beginWriteArray(key);
                for (int i = 0; i < jsonArray.size(); ++i) {
                        m_settings.setArrayIndex(i);
                        QJsonValue arrayValue = jsonArray.at(i);
                        if (arrayValue.isObject()) {
                            parseJsonObject(arrayValue.toObject());
                        } else {
                            m_settings.setValue("value", arrayValue.toVariant());
                        }
                }
                m_settings.endArray();
                break;
            }
            case QJsonValue::Object:
                parseJsonObject(value.toObject(), key);
                break;
            default:
                qWarning("Unsupported JSON value type for key: %s", qPrintable(key));
            }
    }
}


void Settings::setDefaultConfig()
{
    // m_settings.beginGroup("ModelWrapper")
    m_settings.beginGroup("Signals");

    m_settings.endGroup();
}
