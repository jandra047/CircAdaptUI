#ifndef RESETBUTTON_H
#define RESETBUTTON_H

#include <QToolButton>
#include <qtpropertybrowser.h>

class ResetButton : public QToolButton
{

    Q_OBJECT

public:
    ResetButton(QWidget* parent);
    ~ResetButton() = default;

public slots:
    void handlePropertyChanged(QtProperty* property) { setEnabled(property->isModified()); }


};

#endif // RESETBUTTON_H
