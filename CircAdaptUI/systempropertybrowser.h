#ifndef SYSTEMPROPERTYBROWSER_H
#define SYSTEMPROPERTYBROWSER_H

#include "propertybrowserbase.h"

class SystemPropertyBrowser : public PropertyBrowserBase
{
    Q_OBJECT
public:
    SystemPropertyBrowser(QWidget* parent);
    ~SystemPropertyBrowser() {};

    // void handleDynPropertyChanged( QtProperty * property, QVariant & Val ) override;
private:
    QtProperty* mSystemProperties;
private slots:
    void propertyValueChanged( QtProperty * property, QVariant Val ) override; /*handleDynPropertyChanged( property, Val );*/
};

#endif // SYSTEMPROPERTYBROWSER_H
