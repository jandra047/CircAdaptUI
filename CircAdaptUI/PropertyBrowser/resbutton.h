#ifndef RESBUTTON_H
#define RESBUTTON_H

#include <QToolButton>
#include <qtpropertybrowser.h>

class ResButton : public QToolButton
{

    Q_OBJECT

public:
    ResButton(QWidget* parent);
    ~ResButton() = default;

    public slots:
    void handlePropertyChanged(QtProperty* property) { setEnabled(property->isModified()); }


};

#endif // RESBUTTON_H
