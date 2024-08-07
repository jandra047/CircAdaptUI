#include "togglebuttongroup.h"

ToggleButtonGroup::ToggleButtonGroup(QWidget *parent)
    : QWidget(parent), buttonGroup(new QButtonGroup(this)),
    mainLayout(new QHBoxLayout(this)) {
    buttonGroup->setExclusive(true);
    setLayout(mainLayout);
}

void ToggleButtonGroup::addButton(const QString &text) {
    QPushButton *button = new QPushButton(text, this);
    button->setFixedHeight(30);
    button->setCheckable(true);
    button->setStyleSheet("QPushButton { background-color: #a0a0a4; border: 1px solid #000000; }"
                               "QPushButton:checked { background-color: #FFFFFF; }");
    buttonGroup->addButton(button);
    mainLayout->addWidget(button);
}
