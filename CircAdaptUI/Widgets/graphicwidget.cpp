#include "graphicwidget.h"
#include <QVBoxLayout>
#include "modelgraphicsview.h"

GraphicWidget::GraphicWidget(QWidget* parent) :
    QWidget(parent),
    graphicsView(new ModelGraphicsView(parent)),
    topMenuContainer(new QWidget(parent)),
    subMenuContainer(new QWidget(parent))
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    createButtons();

    currentButton = torsoButton;
    torsoButton->setChecked(true);

    mainLayout->setSpacing(0);
    mainLayout->addWidget(topMenuContainer);
    mainLayout->addWidget(graphicsView);
    mainLayout->addWidget(subMenuContainer);
    setLayout(mainLayout);
}

GraphicWidget::~GraphicWidget()
{
    delete graphicsView;
    delete topMenuContainer;
    delete subMenuContainer;
    delete torsoButton;
    delete heartButton;
    delete tissueButton;
    delete currentButton;
}

void GraphicWidget::createButtons()
{
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    torsoButton = new QPushButton("Torso", this);
    torsoButton->setCheckable(true);
    heartButton = new QPushButton("Heart", this);
    heartButton->setCheckable(true);
    tissueButton = new QPushButton("Tissue", this);
    tissueButton->setCheckable(true);

    torsoButton->setStyleSheet("QPushButton { background-color: #a0a0a4; border: 1px solid #000000; }"
                               "QPushButton:checked { background-color: #FFFFFF; }");
    heartButton->setStyleSheet("QPushButton { background-color: #a0a0a4; border: 1px solid #000000; }"
                           "QPushButton:checked { background-color: #FFFFFF; }");
    tissueButton->setStyleSheet("QPushButton { background-color: #a0a0a4; border: 1px solid #000000; }"
                           "QPushButton:checked { background-color: #FFFFFF; }");

    // Set fixed height for buttons
    torsoButton->setFixedHeight(30);
    heartButton->setFixedHeight(30);
    tissueButton->setFixedHeight(30);

    buttonLayout->addWidget(torsoButton);
    buttonLayout->addWidget(heartButton);
    buttonLayout->addWidget(tissueButton);
    topMenuContainer->setLayout(buttonLayout);
    buttonLayout->setContentsMargins(0,0, 0, 0);
    buttonLayout->setSpacing(0);

    // Connect signals and slots
    connect(torsoButton, &QPushButton::clicked, [this] () { handleButtonClick(torsoButton, ViewType::Torso); });
    connect(heartButton, &QPushButton::clicked, [this] () { handleButtonClick(heartButton, ViewType::Heart); });
    connect(tissueButton, &QPushButton::clicked, [this] () { handleButtonClick(tissueButton, ViewType::Tissue); });
}


void GraphicWidget::handleButtonClick(QPushButton *button, ViewType viewType) {
    if (currentButton && currentButton != button) {
        currentButton->setChecked(false);  // Uncheck the previous button
    }

    if (currentButton != button) {
        button->setChecked(true);  // Check the new button
        currentButton = button;  // Update the current button
        graphicsView->showView(viewType);
    } else {
        currentButton = nullptr;  // If the same button is clicked again, deselect it
    }
}
