#include "timesignal.h"
#include <QPixmap>
#include <QPainter>

void TimeSignal::updateGraph(Buffer& buffer, double timeInterval)
{
    // Get all the data from the buffer
    buffer.lock();
    QVector<double> yData = buffer.get(m_yVar, timeInterval);
    QVector<double> tData = buffer.get(m_xVar, timeInterval);
    buffer.unlock();

    // Shift time data to start from current m_xPos
    double dt = tData[1] - tData[0];
    for (int i = 0; i < tData.size(); ++i) {
        tData[i] = m_xPos + i*dt;
    }

    // Remove old data before plotting the new data
    removeData(m_xPos, tData.last() + m_dt);

    // Plot the new data
    addData(tData, yData, true);

    // Update m_xPos for the next segment
    m_xPos = fmod(tData.last(), keyAxis()->range().upper);

}

void TimeSignal::removeData(double const x0, double const x1)
{
    if (x1 > keyAxis()->range().upper)
    {
        data()->removeBefore(fmod(x1, keyAxis()->range().upper));
        data()->removeAfter(x0);
        addData(keyAxis()->range().upper, qQNaN());
    }
    else
    {
        data()->remove(x0, x1);
        addData(x1, qQNaN());
    }
}

void TimeSignal::drawLinePlot(QCPPainter* painter, const QVector<QPointF> &lines) const
{
  if (painter->pen().style() != Qt::NoPen && painter->pen().color().alpha() != 0)
  {
    applyDefaultAntialiasingHint(painter);
    drawPixmap(painter, lines);
  }
}

void TimeSignal::drawPixmap(QCPPainter* painter, const QVector<QPointF> &lines) const
{
    // Ensure pen settings are correct
    if (!painter->modes().testFlag(QCPPainter::pmVectorized) &&
        qFuzzyCompare(painter->pen().widthF(), 1.0))
    {
        QPen newPen = painter->pen();
        newPen.setWidth(0);
        painter->setPen(newPen);
    }
    // Prepare the memory pixmap for drawing
    QSize neededSize = QSize(int(mParentPlot->axisRect()->width()), int(mParentPlot->axisRect()->height()));
    if (mMemSignalPlot.isNull() || mMemSignalPlot.size() != neededSize) {
        mMemSignalPlot = QPixmap(neededSize);
    }
    mMemSignalPlot.fill(Qt::transparent);  // Clear previous content

    // Verify mMemSignalPlot is valid before creating QPainter
    if (!mMemSignalPlot.isNull()) {
        QPainter pixmapPainter(&mMemSignalPlot);
        pixmapPainter.setRenderHint(QPainter::Antialiasing);

        // Set pen from QCPPainter to QPainter
        pixmapPainter.setPen(painter->pen());

        // Draw the signal path on the pixmap
        pixmapPainter.drawPolyline(createPolygon(1));
    }

    // Transfer the pixmap to the main painter
    painter->drawPixmap(mParentPlot->axisRect()->topLeft(), mMemSignalPlot, mMemSignalPlot.rect());
    // painter->fillRect(clearRect(), Qt::red);
}

// QPolygonF TimeSignal::createPolygon() const
// {
//     QPolygonF polygon;

//     for (auto it = data()->constBegin(); it != data()->constEnd(); ++it) {
//         QPointF dataPoint(
//             keyAxis()->coordToPixel(it->key),
//             valueAxis()->coordToPixel(it->value));
//         polygon.append(dataPoint);
//     }

//     return polygon;
// }
QRectF TimeSignal::clearRect() const
{
    QRectF rect(
        keyAxis()->coordToPixel(m_xPos),
        0,
        keyAxis()->coordToPixel(m_xPos + m_dt),
        mMemSignalPlot.height()
        );
    qDebug() << rect.width();
    return rect;
}

QPolygonF TimeSignal::createPolygon(double pixelSize) const
{
    QPolygonF polygon;
    QPointF lastPoint;

    bool firstPoint = true;
    for (auto it = data()->constBegin(); it != data()->constEnd(); ++it)
    {
        // Convert data point to pixel coordinates
        if (qIsNaN(it->key) || qIsNaN(it->value) || qIsInf(it->key) || qIsInf(it->value))
            continue;

        QPointF dataPoint(
        keyAxis()->coordToPixel(it->key),
        valueAxis()->coordToPixel(it->value)
        );

        // If this is the first point or the distance from the last point exceeds pixelSize
        if (firstPoint || QLineF(lastPoint, dataPoint).length() > pixelSize)
        {
        polygon.append(dataPoint);
        lastPoint = dataPoint;
        firstPoint = false;
        }
    }

    return polygon;
}

