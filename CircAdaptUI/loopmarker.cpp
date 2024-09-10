#include "loopmarker.h"


void LoopMarker::draw(QCPPainter* painter)
{
    // Calculate the scale factor based on the current axis ranges
    double xRange = parentPlot()->xAxis->range().size();
    double yRange = parentPlot()->yAxis->range().size();
    // double scale = std::min(xRange, yRange) / 200.0;  // Adjust the scale factor as needed

    // Calculate the new position of the marker based on the current axis ranges
    double xPos = parentPlot()->xAxis->coordToPixel(m_keyPos);
    double yPos = parentPlot()->yAxis->coordToPixel(m_valuePos);

    // Calculate the new size of the marker based on the scale factor
    double radius = m_circleRadius;
    double thickness = m_circleThickness;

    // Set the new size and position of the marker
    topLeft->setCoords(xPos - radius, yPos - radius);
    bottomRight->setCoords(xPos + radius, yPos + radius);

    painter->setPen(QPen(brush().color(), thickness));
    painter->drawEllipse(QRectF(topLeft->coords().x(), topLeft->coords().y(), 2 * radius, 2 * radius));
}

void LoopMarker::setPosition(double key, double value)
{
    m_keyPos = key;
    m_valuePos = value;
}
