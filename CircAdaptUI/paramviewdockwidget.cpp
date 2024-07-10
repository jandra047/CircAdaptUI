#include "paramviewdockwidget.h"
#include "ui_paramviewdockwidget.h"

ParamViewDockWidget::ParamViewDockWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::ParamViewDockWidget)
{
    ui->setupUi(this);
}

ParamViewDockWidget::~ParamViewDockWidget()
{
    delete ui;
}
