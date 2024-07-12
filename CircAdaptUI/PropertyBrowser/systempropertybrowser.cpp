#include "systempropertybrowser.h"
#include "CircAdaptUI/settings.h"

SystemPropertyBrowser::SystemPropertyBrowser(QWidget* parent):
    PropertyBrowserBase(parent)
{
    mSystemProperties = addGroupProperty( tr("Homeostatic control"));
    createDoubleProperty( mSystemProperties,
                          "Heart rate",
                          50,
                          100,
                          5,
                          80,
                          tr("Beats Per Minute") );
    createCheckboxProperty( mSystemProperties,
                            "PFC",
                            true,
                            tr("Enables the pressure flow control, maintaining a constant mean blood pressure") );
}

void SystemPropertyBrowser::propertyValueChanged( QtProperty * property, QVariant  val )
{
    // Update model parameter with new value
}
