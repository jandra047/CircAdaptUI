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

    QString propertyKey(QtProperty* property) const { return m_propertyKeys[property]; }
    void setPropertyKey(QtProperty *property, const QString &key) {
        m_propertyKeys[property] = key;
    }

    void setToDefault(QtProperty* property) { setValue(property, m_defaultValues[property]); }

private:
    QMap<QtProperty*, QVariant> m_defaultValues;
    QMap<QtProperty*, QString> m_propertyKeys;
    // QMap<QtProperty*, ModelParameter*> m_modelParameters;
};

#endif // PROPERTYMANAGER_H
