#include "systempropertybrowser.h"
#include "CircAdaptUI/settings.h"

SystemPropertyBrowser::SystemPropertyBrowser(QWidget* parent):
    PropertyBrowserBase(parent)
{
    setPropertiesFromConfig();
}

void SystemPropertyBrowser::setPropertiesFromConfig()
{
    auto s = Settings::instance().ModelParameters()["Systemic"].toObject();
    for (const QString& key : s.keys())
    {
        mSystemProperties = addGroupProperty( tr(key.toStdString().c_str()) );
        for (auto array_elem : s[key].toArray())
        {
            const QJsonObject obj = array_elem.toObject();

            if (obj["type"].toString() == "double")
            {
                createDoubleProperty(mSystemProperties,
                                     obj["name"].toString(),
                                     obj["min"].toDouble(),
                                     obj["max"].toDouble(),
                                     obj["stepsize"].toDouble(),
                                     obj["default"].toDouble(),
                                     tr(obj["tooltip"].toString().toStdString().c_str()));
            }
            else if (obj["type"].toString() == "bool")
            {
                createCheckboxProperty( mSystemProperties,
                                        obj["name"].toString(),
                                        obj["default"].toBool(),
                                        tr(obj["tooltip"].toString().toStdString().c_str()));

            }
        }
    }
}

void SystemPropertyBrowser::propertyValueChanged( QtProperty * property, QVariant val )
{
    // Update model parameter with new value
}
