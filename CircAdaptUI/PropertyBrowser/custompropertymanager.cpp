#include "custompropertymanager.h"

CustomPropertyManager::CustomPropertyManager(QObject* parent):
    QtVariantPropertyManager(parent)
{

}

QtProperty* CustomPropertyManager::findPropertyByKey(const QString& propertyKey)
{
    for (auto [key, value] : m_propertyKeys.asKeyValueRange())
    {
        if (value == propertyKey)
            return key;
    }
    return Q_NULLPTR;
}
