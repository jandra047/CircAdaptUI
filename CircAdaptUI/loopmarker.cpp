#include "loopmarker.h"


void LoopMarker::draw(QCPPainter* painter)
{
    // Calculate the new position of the marker based on the current axis ranges
    double xPos = parentPlot()->xAxis->coordToPixel(m_keyPos);
    double yPos = parentPlot()->yAxis->coordToPixel(m_valuePos);

    QRectF ellipseRect = QRectF(xPos - m_circleRadius, yPos - m_circleRadius, 2 * m_circleRadius, 2 * m_circleRadius);
    const int clipEnlarge = qCeil(mainPen().widthF());
    QRect clip = clipRect().adjusted(-clipEnlarge, -clipEnlarge, clipEnlarge, clipEnlarge);
    if (ellipseRect.intersects(clip)) // only draw if bounding rect of ellipse is visible in cliprect
    {
      painter->setPen(mainPen());
      painter->setBrush(mainBrush());
    #ifdef __EXCEPTIONS
      try // drawEllipse sometimes throws exceptions if ellipse is too big
      {
    #endif
        painter->drawEllipse(ellipseRect);
    #ifdef __EXCEPTIONS
      } catch (...)
      {
        qDebug() << Q_FUNC_INFO << "Item too large for memory, setting invisible";
        setVisible(false);
      }
    #endif
    }
}

void LoopMarker::setPosition(double key, double value)
{
    m_keyPos = key;
    m_valuePos = value;
}
