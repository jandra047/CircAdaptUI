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
    // obj(new SVGObjectBase(":/CircAdapt/svgs/Full_Body.svg"))
{

    m_torsoView = new SVGObjectBase(":/CircAdapt/svgs/Full_Body.svg");
    m_torsoView->setVisible(true);
    addItem(m_torsoView);
    update();
}
