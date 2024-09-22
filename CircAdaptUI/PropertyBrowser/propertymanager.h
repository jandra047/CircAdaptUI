#ifndef PROPERTYMANAGER_H
#define PROPERTYMANAGER_H

#include "qtvariantproperty.h"

class CustomPropertyManager : public QtVariantPropertyManager
{

    Q_OBJECT

public:
    CustomPropertyManager(QObject* parent = Q_NULLPTR);

    QVariant defaultValue(QtProperty* property) const { return m_defaultValues[property]; }
    void setDefaultValue(QtProperty *property, const QVariant &value) {
        m_defaultValues[property] = value;
    }

    void setToDefault(QtProperty* property) { setValue(property, m_defaultValues[property]); }

private:
    QMap<QtProperty*, QVariant> m_defaultValues;
};

#endif // PROPERTYMANAGER_H
