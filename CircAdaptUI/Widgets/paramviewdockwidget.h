#ifndef PARAMVIEWDOCKWIDGET_H
#define PARAMVIEWDOCKWIDGET_H

#include <QCloseEvent>
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
    void closeEvent( QCloseEvent * event );
public:
signals:
    void paramChanged(const QString& path, const QVariant& value);
    void aboutToClose();
};

#endif // PARAMVIEWDOCKWIDGET_H
