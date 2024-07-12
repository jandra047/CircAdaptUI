#include "modelgraphicsview.h"

ModelGraphicsView::ModelGraphicsView(QWidget* parent):
    QGraphicsView(parent),
    m_SVGViewScene(Q_NULLPTR)
{
    setRenderHint(QPainter::Antialiasing, true);

    m_SVGViewScene = new QGraphicsScene(this);
    setScene(m_SVGViewScene);
    setSceneRect(0, 0, size().width(), size().height());
}
