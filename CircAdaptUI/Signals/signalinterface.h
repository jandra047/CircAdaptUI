#ifndef SIGNALINTERFACE_H
#define SIGNALINTERFACE_H

#include <QObject>
#include "CircAdaptUI/buffer.h"
#include <QColor>

class SignalInterface
{

public:
    SignalInterface();
    SignalInterface(
                   QString displayName,
                   QString yVar,
                   QString xVar = "t",
                   QColor color = QColor(0,0,0),
                   bool isVisible = true,
                   QString unit = "",
                   bool isInMainMenu = true) :
        color(color),
        m_yVar(yVar),
        m_xVar(xVar),
        m_displayName(displayName),
        m_unit(unit),
        m_isInMainMenu(isInMainMenu)
    {
    };

    /*!
     * \brief Update graph with datapoints from buffer based on current FPS
     * \param buffer Buffer object that holds the data
     */
    virtual void updateGraph(Buffer& buffer, double timeInterval) = 0;

    virtual void reset() = 0;

    const QString getXVar() const { return m_xVar; };
    const QString getYVar() const { return m_yVar; };
    const QColor getColor() const { return color; }
    const QString getDisplayName() const { return m_displayName; }
    const QString getUnit() const { return m_unit; }
    const bool isInMainMenu() const { return m_isInMainMenu; }
    const double getXPos() const { return m_xPos; }

protected:

    /*!
     * \brief Name of the variable plotted on the y-axis.
     */
    QString m_yVar;

    /*!
     * \brief Name of the variable plotted on the x-axis.
     */
    QString m_xVar;

    bool m_isInMainMenu;

    QString m_displayName;

    QString m_unit;

    QColor color;

    double m_xPos{0};
    int i{0};
    double m_dt{0.2};
};

#endif // SIGNALINTERFACE_H
