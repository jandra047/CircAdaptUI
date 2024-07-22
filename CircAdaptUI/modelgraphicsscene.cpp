#include "modelgraphicsscene.h"
#include <QSvgRenderer>

ModelGraphicsScene::ModelGraphicsScene(QObject* parent):
    QGraphicsScene(parent)
    // mTorsoView( nullptr ),
    // mHeartView( nullptr ),
    // mTissueView( nullptr ),
    // mTorsoSceneSwitchPtr( nullptr ),
    // mHeartSceneSwitchPtr( nullptr ),
    // mTissueSceneSwitchPtr( nullptr ),
    // mSelectedType( PSceneSwitch::sTorso ),
    // mMouseDownDeteced( false ),
    // mSelectedElementPtr( nullptr )
{

    // mTorsoView = new PTorsoViewItem();
    // mTorsoView->setVisible(true);
    QString s( ":/CircAdapt/svgs/Full_Body.svg" );
    QSvgRenderer* renderer = new QSvgRenderer(s, this);
    mBackGroundItem = new QGraphicsSvgItem(s);
    addItem(mBackGroundItem);
    mBackGroundItem->setSharedRenderer(renderer);
    mBackGroundItem->setActive(true);
    mBackGroundItem->setVisible(true);
    mBackGroundItem->show();
    mBackGroundItem->setZValue( 1 );
    update();
}
