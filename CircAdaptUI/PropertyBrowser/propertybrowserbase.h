#ifndef PROPERTYBROWSERBASE_H
#define PROPERTYBROWSERBASE_H

#include <QWidget>
#include <QGridLayout>
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "customeditorfactory.h"
#include "custompropertymanager.h"

class PropertyBrowserBase : public QWidget
{
    Q_OBJECT

public:
    PropertyBrowserBase(QWidget* parent = Q_NULLPTR);
    ~PropertyBrowserBase();

    QGridLayout* mGrid;
    QtTreePropertyBrowser* mPBrowser;
    QtGroupPropertyManager* mGroupManager;
    CustomPropertyManager* mDynPropertyManager;
    PropertyFactory* mResetPropertyFactory;

    QtProperty* addGroupProperty(const QString& name);
    void createDoubleProperty(QtProperty* property,
                              const QString& pName,
                              double minVal,
                              double maxVal,
                              double singleStep,
                              double setVal,
                              const QString& key,
                              const QString& toolTip,
                              const QString& unit = "",
                              bool enabled = true);
    void createCheckboxProperty( QtProperty * property,
                                 const QString & pName,
                                 const QString & key,
                                 bool SetVal,
                                 const QString & toolTipVal );

    QMap<QString, QList<QtBrowserItem*>> createProperties(const QJsonObject& jsonObject);
signals:
    void changeModelParam(const QString& path, const QVariant& value);
private slots:
    void propertyValueChanged( QtProperty * property, const QVariant& Val ); /*handleDynPropertyChanged( property, Val );*/
public slots:
    void showProperties(QList<QtBrowserItem*> browserItems);
    void resetProperties();
};

#endif // PROPERTYBROWSERBASE_H
