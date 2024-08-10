#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "viewtypes.h"
#include "CircAdaptUI/SVGviews/togglebuttongroup.h"
#include "CircAdaptUI/Widgets/modelgraphicsview.h"

class GraphicWidget : public QWidget
{
public:
    using ViewType = vt::ViewType;

    GraphicWidget(QWidget* parent);
    ~GraphicWidget();

    QPushButton* torsoButton;
    QPushButton* heartButton;
    QPushButton* tissueButton;
    QPushButton* currentButton;

private:
    ModelGraphicsView* graphicsView;
    ToggleButtonGroup* topMenuContainer;
    ToggleButtonGroup* subMenuContainer;
    QHBoxLayout* subMenuLayout;

    void createButtons();
    void topMenuSwitch(QPushButton *button, ViewType viewType);
};

#endif // GRAPHICWIDGET_H
