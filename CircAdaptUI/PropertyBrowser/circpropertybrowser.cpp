#include "circpropertybrowser.h"
#include "CircAdaptUI/settings.h"

CircPropertyBrowser::CircPropertyBrowser(QWidget* parent):
    PropertyBrowserBase(parent),
    m_Properties(Q_NULLPTR)
{
    auto s = Settings::instance().ModelParameters()["Systemic circulation"].toObject();
    for (const QString& key : s.keys())
    {
        m_Properties = addGroupProperty( tr(key.toStdString().c_str()) );
        for (auto array_elem : s[key].toArray())
        {
            const QJsonObject obj = array_elem.toObject();

            if (obj["type"].toString() == "double")
            {
                createDoubleProperty(m_Properties,
                                     obj["name"].toString(),
                                     obj["min"].toDouble(),
                                     obj["max"].toDouble(),
                                     obj["stepsize"].toDouble(),
                                     obj["default"].toDouble(),
                                     tr(obj["tooltip"].toString().toStdString().c_str()),
                                     obj["enabled"].toBool());
            }
            else if (obj["type"].toString() == "bool")
            {
                createCheckboxProperty( m_Properties,
                                        obj["name"].toString(),
                                        obj["default"].toBool(),
                                        tr(obj["tooltip"].toString().toStdString().c_str()));

            }
        }
    }
}
