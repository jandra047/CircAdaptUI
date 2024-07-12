#ifndef PARAMVIEWDOCKWIDGET_H
#define PARAMVIEWDOCKWIDGET_H

#include <QDockWidget>

class QtProperty;

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
public:
signals:
    void paramChanged(const QString& path, const QVariant& value);
};

#endif // PARAMVIEWDOCKWIDGET_H
