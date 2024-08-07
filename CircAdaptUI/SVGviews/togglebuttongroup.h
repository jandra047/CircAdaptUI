#ifndef TOGGLEBUTTONGROUP_H
#define TOGGLEBUTTONGROUP_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>

class ToggleButtonGroup : public QWidget {
    Q_OBJECT

public:
    explicit ToggleButtonGroup(QWidget *parent = nullptr);
    void addButton(const QString &text);

private:
    QButtonGroup *buttonGroup;
    QHBoxLayout *mainLayout;
};

#endif // TOGGLEBUTTONGROUP_H
