#ifndef MODELGRAPHICSVIEW_H
#define MODELGRAPHICSVIEW_H

#include <QGraphicsView>
#include "CircAdaptUI/modelgraphicsscene.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsSvgItem>
#include <QFile>
#include <QMessageBox>
#include <QSvgRenderer>

class ModelGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    ModelGraphicsView(QWidget* parent = Q_NULLPTR);

private:
    ModelGraphicsScene* m_SVGViewScene;
};


// class ModelGraphicsView : public QGraphicsView
// {
//     Q_OBJECT

// public:
//     ModelGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent)
//     {
//         scene = new QGraphicsScene(this);
//         setScene(scene);

//         // Load SVG items
//         torsoSvg = new QGraphicsSvgItem(":/CircAdapt/svgs/Full_Body.svg");
//         heartSvg = new QGraphicsSvgItem(":/CircAdapt/svgs/Heart.svg");
//         tissueSvg = new QGraphicsSvgItem(":/CircAdapt/svgs/Heart_segments.svg");

//         // Add items to scene
//         scene->addItem(torsoSvg);
//         scene->addItem(heartSvg);
//         scene->addItem(tissueSvg);

//         // Initially, only show torso
//         heartSvg->setVisible(false);
//         tissueSvg->setVisible(false);

//         // Create buttons
//         torsoButton = new QPushButton("Torso", this);
//         heartButton = new QPushButton("Heart", this);
//         tissueButton = new QPushButton("Tissue", this);

//         // Connect buttons
//         connect(torsoButton, &QPushButton::clicked, this, &ModelGraphicsView::showTorso);
//         connect(heartButton, &QPushButton::clicked, this, &ModelGraphicsView::showHeart);
//         connect(tissueButton, &QPushButton::clicked, this, &ModelGraphicsView::showTissue);

//         // Create layout for buttons
//         QHBoxLayout *buttonLayout = new QHBoxLayout();
//         buttonLayout->addWidget(torsoButton);
//         buttonLayout->addWidget(heartButton);
//         buttonLayout->addWidget(tissueButton);

//         // Create main layout
//         QVBoxLayout *mainLayout = new QVBoxLayout(this);
//         mainLayout->addLayout(buttonLayout);

//         // Set the layout on the QGraphicsView
//         setLayout(mainLayout);

//         // Set scene rect to fit content
//         scene->setSceneRect(scene->itemsBoundingRect());
//     }

// protected:
//     void resizeEvent(QResizeEvent *event) override
//     {
//         QGraphicsView::resizeEvent(event);
//         fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
//     }

// private slots:
//     void showTorso()
//     {
//         torsoSvg->setVisible(true);
//         heartSvg->setVisible(false);
//         tissueSvg->setVisible(false);
//         scene->setSceneRect(torsoSvg->boundingRect());
//         fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
//     }

//     void showHeart()
//     {
//         torsoSvg->setVisible(false);
//         heartSvg->setVisible(true);
//         tissueSvg->setVisible(false);
//         scene->setSceneRect(heartSvg->boundingRect());
//         fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
//     }

//     void showTissue()
//     {
//         torsoSvg->setVisible(false);
//         heartSvg->setVisible(false);
//         tissueSvg->setVisible(true);
//         scene->setSceneRect(tissueSvg->boundingRect());
//         fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
//     }

// private:
//     QGraphicsScene *scene;
//     QGraphicsSvgItem *torsoSvg;
//     QGraphicsSvgItem *heartSvg;
//     QGraphicsSvgItem *tissueSvg;
//     QPushButton *torsoButton;
//     QPushButton *heartButton;
//     QPushButton *tissueButton;
// };


#endif // MODELGRAPHICSVIEW_H
