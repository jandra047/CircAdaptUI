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
        qDebug() << key << "\n";
        qDebug() << s[key].toArray();
        mSystemProperties = addGroupProperty( tr(key.toStdString().c_str()) );
        for (auto array_elem : s[key].toArray())
        {
            const QJsonObject obj = array_elem.toObject();
            createDoubleProperty(mSystemProperties,
                                 obj["name"].toString(),
                                 obj["min"].toDouble(),
                                 obj["max"].toDouble(),
                                 obj["stepsize"].toDouble(),
                                 obj["default"].toDouble(),
                                 tr(obj["tooltip"].toString().toStdString().c_str()));
        }
    }
    createCheckboxProperty( mSystemProperties,
                            "Homeostatic pressure-flow control",
                            true,
                            tr("Enables the pressure flow control, maintaining a constant mean blood pressure") );
}

void SystemPropertyBrowser::propertyValueChanged( QtProperty * property, QVariant val )
{
    // Update model parameter with new value
}
