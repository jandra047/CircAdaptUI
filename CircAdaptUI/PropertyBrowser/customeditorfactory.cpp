#include "customeditorfactory.h"
#include "resetbutton.h"
#include <QHBoxLayout>

PropertyFactory::PropertyFactory( CustomPropertyManager* manager, QWidget * parent ) :  // QWidget *subEditor, bool resettable, QtAbstractPropertyManager *manager, QtProperty *property, QWidget *parent
    QtVariantEditorFactory( parent ),
    m_manager(manager)
{
}


QWidget * PropertyFactory::createEditor( QtVariantPropertyManager * manager, QtProperty * property, QWidget * parent )
{
    // Create the standard editor based on property type
    QWidget *editor = QtVariantEditorFactory::createEditor(manager, property, parent);

    // Create a container widget to hold the layout
    QWidget *container = new QWidget(parent);
    // Create a reset button
    ResetButton *resetButton = createToolButton(property, editor);
    // Create a layout to hold the editor and button side by side
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(editor);
    layout->addWidget(resetButton);
    layout->setContentsMargins(0, 0, 0, 0);  // Remove margins for a clean layout

    container->setLayout(layout);

    // Connect the button's clicked signal to a slot or lambda to reset the property value
    connect(resetButton, &QToolButton::clicked, this, [this, property, resetButton]() {
        handleResetButtonClick(property, resetButton);
    });

    return container;
}

void PropertyFactory::handleResetButtonClick(QtProperty *property, QToolButton* button)
{
    if (property) {
        m_manager->setToDefault(property);
        property->setModified(false);
        button->setEnabled(false);
    }
}

ResetButton* PropertyFactory::createToolButton(QtProperty* property, QWidget* widget)
{
    ResetButton* resetButton = new ResetButton(widget);
    resetButton->setEnabled(property->isModified());
    QPixmap pixmap( ":/CircAdapt/icons/undo.png");
    resetButton->setIcon(pixmap);
    resetButton->setIconSize(QSize(10,10));
    resetButton->setToolTip("Reset to default");

    resetButton->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::MinimumExpanding ) );

    // Connect the button's clicked signal to a slot or lambda to reset the property value
    connect(resetButton, &QToolButton::clicked, this, [this, property, resetButton]() {
        handleResetButtonClick(property, resetButton);
    });
    connect(resetButton, &QToolButton::destroyed, resetButton, &QToolButton::deleteLater);

    connect( property->propertyManager(), &QtVariantPropertyManager::propertyChanged,
            resetButton, &ResetButton::handlePropertyChanged);

    return resetButton;
}
