#ifndef PROPERTYBROWSERBASE_H
#define PROPERTYBROWSERBASE_H

#include <QWidget>
#include <QGridLayout>
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "propertyfactory.h"

class PropertyBrowserBase : public QWidget
{
    Q_OBJECT

public:
    PropertyBrowserBase(QWidget* parent = Q_NULLPTR);
    ~PropertyBrowserBase() {};

    QGridLayout* mGrid;
    QtTreePropertyBrowser* mPBrowser;
    QtGroupPropertyManager* mGroupManager;
    QtVariantPropertyManager* mDynPropertyManager;
    PropertyFactory* mResetPropertyFactory;

    QtProperty* addGroupProperty(const QString& name);
    void createDoubleProperty(QtProperty* property,
                              const QString& pName,
                              double minVal,
                              double maxVal,
                              double singleStep,
                              double setVal,
                              const QString& toolTip,
                              bool enabled = true);
    void createCheckboxProperty( QtProperty * property,
                                 const QString & pName,
                                 bool SetVal,
                                 const QString & toolTipVal );
protected:
    // virtual void handleDynPropertyChanged( QtProperty * property, QVariant & Val ) = 0;
private slots:
    virtual void propertyValueChanged( QtProperty * property, QVariant Val )  = 0; /*handleDynPropertyChanged( property, Val );*/
};

#endif // PROPERTYBROWSERBASE_H
