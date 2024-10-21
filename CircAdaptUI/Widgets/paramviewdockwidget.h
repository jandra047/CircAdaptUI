#ifndef PARAMVIEWDOCKWIDGET_H
#define PARAMVIEWDOCKWIDGET_H

#include <QCloseEvent>
#include <QDockWidget>

class QtProperty;
class Buffer;

namespace Ui {
class ParamViewDockWidget;
}

class ParamViewDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ParamViewDockWidget(QWidget *parent = nullptr);
    ~ParamViewDockWidget();

    void resetProperties();

private:
    Ui::ParamViewDockWidget *ui;
    void closeEvent( QCloseEvent * event ) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
signals:
    void paramChanged(const QString& path, const QVariant& value);
    void aboutToClose();
public slots:
    void showOxygen(bool isVisible);
    void updateOxygen(Buffer& buffer);
};

#endif // PARAMVIEWDOCKWIDGET_H
