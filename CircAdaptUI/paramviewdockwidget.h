#ifndef PARAMVIEWDOCKWIDGET_H
#define PARAMVIEWDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class ParamViewDockWidget;
}

class ParamViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ParamViewDockWidget(QWidget *parent = nullptr);
    ~ParamViewDockWidget();

private:
    Ui::ParamViewDockWidget *ui;
};

#endif // PARAMVIEWDOCKWIDGET_H
