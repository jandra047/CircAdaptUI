#ifndef PROPERTYBROWSERBASE_H
#define PROPERTYBROWSERBASE_H

#include <QWidget>
#include <QGridLayout>
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"

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
    QtVariantEditorFactory* mResetPropertyFactory;

    QtProperty* addGroupProperty(const QString& name);
    void createDoubleProperty(QtProperty* property,
                              const QString& pName,
                              double minVal,
                              double maxVal,
                              double singleStep,
                              double setVal,
                              const QString& toolTip,
                              const QString& path,
                              bool enabled = true);
    void createCheckboxProperty( QtProperty * property,
                                 const QString & pName,
                                 bool SetVal,
                                 const QString & toolTipVal );
private:
    QMap<QtProperty*, QString> m_paths;
signals:
    void changeModelParam(const QString& path, const QVariant& value);
private slots:
    void propertyValueChanged( QtProperty * property, const QVariant& Val ); /*handleDynPropertyChanged( property, Val );*/
};

#endif // PROPERTYBROWSERBASE_H
