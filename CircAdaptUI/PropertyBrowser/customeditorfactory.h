#ifndef CUSTOMEDITORFACTORY_H
#define CUSTOMEDITORFACTORY_H

#include "qtvariantproperty.h"
#include "custompropertymanager.h"
#include "resetbutton.h"

class PropertyFactory : public QtVariantEditorFactory
{
    Q_OBJECT

public:
    PropertyFactory(CustomPropertyManager* manager, QWidget* parent = Q_NULLPTR);
    virtual ~PropertyFactory(void) {};
protected:
    QWidget * createEditor( QtVariantPropertyManager * manager, QtProperty * property, QWidget * parent ) override;
private:
    ResetButton* createToolButton(QtProperty* property, QWidget* widget);
    CustomPropertyManager* m_manager;

private slots:
    void handleResetButtonClick(QtProperty *property, QToolButton* button);
};

#endif // CUSTOMEDITORFACTORY_H
