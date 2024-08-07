#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "CircAdaptUI/Widgets/modelgraphicsview.h"
#include "viewtypes.h"

class GraphicWidget : public QWidget
{
public:
    GraphicWidget(QWidget* parent);
    ~GraphicWidget();

    QPushButton* torsoButton;
    QPushButton* heartButton;
    QPushButton* tissueButton;
    QPushButton* currentButton;

private:
    ModelGraphicsView* graphicsView;
    QWidget* topMenuContainer;
    QWidget* subMenuContainer;
    QHBoxLayout* subMenuLayout;

    void createButtons();
    void topMenuSwitch(QPushButton *button, ViewType viewType);
};

#endif // GRAPHICWIDGET_H
