#ifndef CIRCPROPERTYBROWSER_H
#define CIRCPROPERTYBROWSER_H

#include <QObject>
#include "propertybrowserbase.h"

class CircPropertyBrowser: public PropertyBrowserBase
{
    Q_OBJECT
public:
    CircPropertyBrowser(QWidget* parent);

private:
    QtProperty* m_Properties;
};

#endif // CIRCPROPERTYBROWSER_H
