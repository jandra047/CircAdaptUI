#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H

#include "qtvariantproperty.h"
#include "propertymanager.h"
#include "resbutton.h"

class PropertyFactory : public QtVariantEditorFactory
{
    Q_OBJECT

public:
    PropertyFactory(CustomPropertyManager* manager, QWidget* parent = Q_NULLPTR);
    virtual ~PropertyFactory(void) {};
protected:
    QWidget * createEditor( QtVariantPropertyManager * manager, QtProperty * property, QWidget * parent ) override;
private:
    ResButton* createToolButton(QtProperty* property, QWidget* widget);
    CustomPropertyManager* m_manager;

private slots:
    void handleResetButtonClick(QtProperty *property, QToolButton* button);
};

#endif // PROPERTYFACTORY_H
