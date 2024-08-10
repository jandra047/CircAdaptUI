#include "graphicwidget.h"
#include <QVBoxLayout>
#include "modelgraphicsview.h"

GraphicWidget::GraphicWidget(QWidget* parent) :
    QWidget(parent),
    graphicsView(new ModelGraphicsView(parent)),
    topMenuContainer(new ToggleButtonGroup(parent))
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    createButtons();

    currentButton = torsoButton;
    torsoButton->setChecked(true);

    mainLayout->setSpacing(0);
    mainLayout->addWidget(topMenuContainer);
    mainLayout->addWidget(graphicsView);
    // mainLayout->addWidget(subMenuContainer);
    subMenuLayout = new QHBoxLayout();
    subMenuContainer = graphicsView->getSubMenu(ViewType::Torso);
    subMenuLayout->addWidget(subMenuContainer);
    mainLayout->addLayout(subMenuLayout);
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
    torsoButton = topMenuContainer->addButton("System");
    heartButton = topMenuContainer->addButton("Heart");
    tissueButton = topMenuContainer->addButton("Tissue");

    // Connect signals and slots
    connect(torsoButton, &QPushButton::clicked, [this] () { topMenuSwitch(torsoButton, ViewType::Torso); });
    connect(heartButton, &QPushButton::clicked, [this] () { topMenuSwitch(heartButton, ViewType::Heart); });
    connect(tissueButton, &QPushButton::clicked, [this] () { topMenuSwitch(tissueButton, ViewType::Tissue); });
}


void GraphicWidget::topMenuSwitch(QPushButton *button, ViewType viewType) {

    if (currentButton != button) {
        currentButton->setChecked(false);
        button->setChecked(true);
        currentButton = button;
        graphicsView->showView(viewType);

        if (subMenuContainer) {
            subMenuLayout->removeWidget(subMenuContainer);
            subMenuContainer->hide();
        }

        ToggleButtonGroup* newSubMenu = graphicsView->getSubMenu(viewType);
        if (newSubMenu) {
            subMenuLayout->addWidget(newSubMenu);
            newSubMenu->show();
        }

        subMenuContainer = newSubMenu;

        update();
    }
    else {
        currentButton->setChecked(true);
    }
}