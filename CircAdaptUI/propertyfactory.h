#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H

#include "qtvariantproperty.h"

class PropertyFactory : public QtVariantEditorFactory
{
    Q_OBJECT

public:
    PropertyFactory(QWidget* parent = Q_NULLPTR);
    virtual ~PropertyFactory(void) {};
};

#endif // PROPERTYFACTORY_H
