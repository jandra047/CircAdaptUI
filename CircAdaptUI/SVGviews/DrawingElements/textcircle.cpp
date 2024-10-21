#include "textcircle.h"
#include <QPainter>
#include <QTextDocument>

TextCircle::TextCircle(QString name, QPointF center, SVGObjectBase* parent):
    QGraphicsTextItem(parent),
    m_Alignment( Qt::AlignHCenter ),
    m_name(name),
    m_Center(center),
    m_CircleBounds()
{
    setScale(0.35);

    setText("999");
    updateCircleBounds();
    if ( document() )
    {
        QTextOption textOption = document()->defaultTextOption();

        textOption.setAlignment( m_Alignment );

        document()->setDefaultTextOption( textOption );
    }
}

void TextCircle::updateCircleBounds()
{

    QFontMetrics metrics( font() );

    // Construct a circle bounding box based on the font configuration
    m_CircleBounds = metrics.boundingRect( "100" );
    m_CircleBounds.moveTop( 0.0 );   // For some reason the top coordinate contains a negative value we neglect
    m_CircleBounds.moveLeft( 0.0 );

    // Find the circle diameter based on the length between the two top-left to r0ght-bottom corners
    qreal biggestLength = sqrt( (m_CircleBounds.width() * m_CircleBounds.width()) + (m_CircleBounds.height() * m_CircleBounds.height()) );

    m_CircleBounds.setWidth( biggestLength );
    m_CircleBounds.setHeight( biggestLength );

    // We must explicitly set the text width for the non-circle item because otherwise the centered or right alignment won't work
    setTextWidth( -1 );
}

void TextCircle::setText(const QString& text)
{
    QRectF          textBounds;
    qreal           verticlePos;                    // The verticle alignment will always be centered
    Qt::Alignment   alignmentFlags = m_Alignment;

    if ( text.contains( QChar( '<' ) ) )
    {
        setHtml( text );
    }
    else
    {
        setPlainText( text );
    }

    // Get the bounding rectangle based on the new text
    textBounds = boundingRect();

    if ( m_CircleBounds.isValid() && (m_CircleBounds.contains( textBounds )) )
    {
        verticlePos = m_Center.y() - ((m_CircleBounds.height() * scale()) / 2.0);

        // The circle defines the bounding box
        if ( alignmentFlags.testFlag( Qt::AlignLeft ) )
        {
            setPos( m_Center.x(), verticlePos );
        }
        else if ( alignmentFlags.testFlag( Qt::AlignHCenter ) )
        {
            // With the center option we also want to align vertically centered because this option should be used when showing the bounding circle
            setPos( m_Center.x() - ((m_CircleBounds.width() * scale()) / 2.0), verticlePos );
        }
        else    // Align right
        {
            setPos( m_Center.x() - (m_CircleBounds.width() * scale()), verticlePos );
        }
    }
    else
    {
        verticlePos = m_Center.y() - ((textBounds.height() * scale()) / 2.0);

        // Adjust the position of this item to the bounding text so it keeps centered at the desired position
        if ( Qt::AlignLeft == m_Alignment )
        {
            setPos( m_Center.x(), verticlePos );
        }
        else if ( (Qt::AlignCenter == m_Alignment) || (Qt::AlignHCenter == m_Alignment) )
        {
            // With the center option we also want to align vertically centered because this option should be used when showing the bounding circle
            setPos( m_Center.x() - ((textBounds.width() * scale()) / 2.0), verticlePos );
        }
        else
        {
            setPos( m_Center.x() - (textBounds.width() * scale()), verticlePos );
        }

        // We must explicitly set the text width for the non-circle item because otherwise the centered or right alignment won't work
        // For the circle item the text width will be set when the circle bound will be determined
        setTextWidth( textBounds.width() );
    }
}

QRectF TextCircle::boundingRect() const
{
    if ( m_CircleBounds.isValid() )
    {
        return m_CircleBounds;
    }
    else
    {
        return QGraphicsTextItem::boundingRect();
    }
}

void TextCircle::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    if ( true )
    {
        QBrush  curBrush( painter->brush() );
        QBrush  bgBrush( Qt::lightGray );
        bool    isClipping = painter->hasClipping();

        // Disabe clipping because the circle is being drawn outside the bounding text box, so outside this items bounding box
        painter->setClipping( false );

        painter->setBrush( bgBrush );
        painter->drawEllipse( m_CircleBounds );

        // Restore previous parameters
        painter->setClipping( isClipping );
        painter->setBrush( curBrush );  // Restore the old brush used


        // // We do not use the base implemnetation to draw the values. The bounding box of the underlying page
        // // in the QTextDocument will nogt be equal to the items bounding rectangle and thus the alignment will
        // // be incorrect.
        // // When at this point in the code, the values will contain the oxigen values in the heart model view so
        // // we know that the text to show contains only simple values. Draw them directly using the painter object
        QFont           currentFont( font() );
        QFontMetrics    metrics( currentFont );
        QString         plainText( toPlainText() );
        QRectF          textRect( metrics.boundingRect( plainText ) );

        // // Position the target rectangle correctly
        textRect.moveTopLeft( QPointF( 0.0, 0.0 ) );
        textRect.moveLeft( (m_CircleBounds.width() - textRect.width()) / 2.0 );
        textRect.moveTop( (m_CircleBounds.height() - textRect.height()) / 2.0 );

        painter->setPen(QPen(QColor(0x666666)));
        painter->drawText( textRect, plainText );
    }
    else
    {
        // Use the default underlying document drawing
        QGraphicsTextItem::paint( painter, option, widget );
    }
}

void TextCircle::update(Buffer& buffer)
{
    setText(
        QString::number(
            buffer.get(m_name)*100, 'f', 0
        )
    );
}
