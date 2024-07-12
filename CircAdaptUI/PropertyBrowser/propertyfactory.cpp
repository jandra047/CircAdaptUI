#include "propertyfactory.h"

PropertyFactory::PropertyFactory( QWidget * parent ) :  // QWidget *subEditor, bool resettable, QtAbstractPropertyManager *manager, QtProperty *property, QWidget *parent
    QtVariantEditorFactory( parent )
    // mResetDecorator( nullptr )
{
    // mResetDecorator = new PPropertyResetDecorator( this );

    // if ( mResetDecorator )
    // {
    //     // Pass on the signal
    //     connect( mResetDecorator, SIGNAL( resetProperty( QtProperty * ) ),
    //              this, SIGNAL( resetProperty( QtProperty * ) ) );
    // }
}
