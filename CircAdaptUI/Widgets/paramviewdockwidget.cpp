#include "paramviewdockwidget.h"
#include "ui_paramviewdockwidget.h"

ParamViewDockWidget::ParamViewDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ParamViewDockWidget)
{
    setVisible(false);
    ui->setupUi(this);
    ui->graphicsView->setup(ui->circPBrowser);
    ui->splitter->setChildrenCollapsible( false );
    ui->graphicsView->setMinimumWidth(400);
    ui->systemPBrowser->setMinimumWidth( 300 );

    QObject::connect(ui->systemPBrowser, &PropertyBrowserBase::changeModelParam,
                     this, [=](const QString& path, const QVariant& val) { emit paramChanged(path,val); } );
    QObject::connect(ui->circPBrowser, &PropertyBrowserBase::changeModelParam,
                     this, [=](const QString& path, const QVariant& val) { emit paramChanged(path,val); } );
    // TODO:
    QObject::connect(ui->graphicsView->graphicsView, &ModelGraphicsView::showProperties,
                     ui->circPBrowser, &PropertyBrowserBase::showProperties);
}

ParamViewDockWidget::~ParamViewDockWidget()
{
    delete ui;
}

void ParamViewDockWidget::closeEvent( QCloseEvent * event )
{
    emit aboutToClose();

    QDockWidget::closeEvent( event );
}

void ParamViewDockWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        this->close();
    } else {
        QDockWidget::keyPressEvent(event);  // Call base class implementation for other keys
    }
}

void ParamViewDockWidget::resetProperties()
{
    ui->systemPBrowser->resetProperties();
    ui->circPBrowser->resetProperties();
}
