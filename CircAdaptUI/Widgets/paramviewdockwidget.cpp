#include "paramviewdockwidget.h"
#include "ui_paramviewdockwidget.h"

ParamViewDockWidget::ParamViewDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ParamViewDockWidget)
{
    ui->setupUi(this);
    ui->splitter->setChildrenCollapsible( false );
    // ui->circModelView->setMinimumWidth( 200 );
    ui->systemPBrowser->setMinimumWidth( 200 );
}

ParamViewDockWidget::~ParamViewDockWidget()
{
    delete ui;
}
