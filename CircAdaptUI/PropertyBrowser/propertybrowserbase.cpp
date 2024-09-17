#include "propertybrowserbase.h"
#include <QJsonObject>
#include <QJsonArray>

PropertyBrowserBase::PropertyBrowserBase(QWidget* parent):
    QWidget(parent),
    mGrid(Q_NULLPTR)
{
    mGrid = new QGridLayout(this);
    mPBrowser = new QtTreePropertyBrowser(this);
    mPBrowser->setResizeMode(QtTreePropertyBrowser::Interactive);
    mGrid->addWidget(mPBrowser);
    mGroupManager = new QtGroupPropertyManager(mPBrowser);
    mDynPropertyManager = new QtVariantPropertyManager( mPBrowser );
    mResetPropertyFactory = new QtVariantEditorFactory(mPBrowser);
    mPBrowser->setFactoryForManager(mDynPropertyManager, mResetPropertyFactory);
    connect( mDynPropertyManager, &QtVariantPropertyManager::valueChanged,
            this, &PropertyBrowserBase::propertyValueChanged );
    mPBrowser->setResizeMode(QtTreePropertyBrowser::ResizeToContents);
}

QtProperty* PropertyBrowserBase::addGroupProperty(const QString& name)
{
    QtProperty* property = mGroupManager->addProperty(name);
    mPBrowser->insertProperty(property, Q_NULLPTR);
    return property;
}

void PropertyBrowserBase::createDoubleProperty(QtProperty* property,
                          const QString& pName,
                          double minVal,
                          double maxVal,
                          double singleStep,
                          double setVal,
                          const QString& toolTip,
                          bool enabled)
{
    QtProperty * doubleProp = mDynPropertyManager->addProperty( QMetaType::Double, pName );

    if ( doubleProp )
    {
        doubleProp->setPropertyName( pName ); // Create a user interface readable name

        doubleProp->setEnabled( enabled );

        if ( !toolTip.isEmpty() )
        {
            doubleProp->setToolTip( toolTip );
        }

        mDynPropertyManager->setAttribute( doubleProp, QLatin1String( "minimum" ), QVariant( minVal ) );
        mDynPropertyManager->setAttribute( doubleProp, QLatin1String( "maximum" ), QVariant( maxVal ) );
        mDynPropertyManager->setAttribute( doubleProp, QLatin1String( "singleStep" ), QVariant( singleStep ) );
        mDynPropertyManager->setAttribute( doubleProp, QLatin1String( "decimals" ), QVariant( 1 ) );

        mDynPropertyManager->setValue( doubleProp, setVal );

        property->addSubProperty( doubleProp ) ;
    }

}

void PropertyBrowserBase::createCheckboxProperty( QtProperty * property,
                                                   const QString & pName,
                                                   bool SetVal,
                                                   const QString & toolTipVal )
{
    // in this function,, the given property will be created and filled with data.
    QtProperty * ckeckboxProp = mDynPropertyManager->addProperty( QMetaType::Bool, pName );

    if ( ckeckboxProp )
    {
        ckeckboxProp->setPropertyName( pName );   // Create a user interface readable name

        if ( !toolTipVal.isEmpty() )
        {
            ckeckboxProp->setToolTip( toolTipVal );
        }

        mDynPropertyManager->setValue( ckeckboxProp, SetVal );

        property->addSubProperty( ckeckboxProp );
    }
}

void PropertyBrowserBase::propertyValueChanged(QtProperty* property, const QVariant& value)
{
    emit changeModelParam(property->propertyName(), value);
}

QtProperty* PropertyBrowserBase::findProperty(const QString& name)
{
    QSet<QtProperty*> properties = mDynPropertyManager->properties();
    for (QtProperty* property : properties)
    {
        if (property->propertyName() == name)
        {
            return property;
        }
    }
    return Q_NULLPTR;
}

QMap<QString, QList<QtBrowserItem*>> PropertyBrowserBase::createProperties(const QJsonObject& jsonObject)
{
    QMap<QString, QList<QtBrowserItem*>> propertyMap {};
    for (const QString& key : jsonObject.keys())
    {
        QList<QtBrowserItem*> list {};
        // QtProperty* properties = addGroupProperty( tr(key.toStdString().c_str()) );
        QtProperty* properties = mGroupManager->addProperty( tr(key.toStdString().c_str()) );
        list.append(mPBrowser->insertProperty(properties, Q_NULLPTR));
        for (auto array_elem : jsonObject[key].toArray())
        {
            const QJsonObject obj = array_elem.toObject();

            if (obj["type"].toString() == "double")
            {
                createDoubleProperty(properties,
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
                createCheckboxProperty( properties,
                                        obj["name"].toString(),
                                        obj["default"].toBool(),
                                        tr(obj["tooltip"].toString().toStdString().c_str()));

            }
        }
        propertyMap[key] = list;
    }

    return propertyMap;

}

void PropertyBrowserBase::showProperties(QList<QtBrowserItem*> browserItems)
{
    for (auto item : mPBrowser->topLevelItems())
    {
        mPBrowser->setItemVisible(item, browserItems.contains(item));
    }
}
