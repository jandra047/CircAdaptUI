#include "paramviewdockwidget.h"
#include "ui_paramviewdockwidget.h"

ParamViewDockWidget::ParamViewDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ParamViewDockWidget)
{
    setVisible(false);
    ui->setupUi(this);
    ui->splitter->setChildrenCollapsible( false );
    ui->graphicsView->setMinimumWidth(400);
    ui->systemPBrowser->setMinimumWidth( 300 );

    // QObject::connect(ui->systemPBrowser->mDynPropertyManager, &QtVariantPropertyManager::valueChanged,
    //                  this, [=](QtProperty* p, const QVariant& v) { emit paramChanged(p,v); } );
    QObject::connect(ui->systemPBrowser, &PropertyBrowserBase::changeModelParam,
                     this, [=](const QString& path, const QVariant& val) { emit paramChanged(path,val); } );
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
