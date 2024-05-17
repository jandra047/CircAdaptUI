#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <modelwrapper.h>
#include "graphgrid.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer(this);
    ModelWrapper mw;
    GraphGrid* a = new GraphGrid(2,3, this);
private slots:
    void on_actionPlay_triggered();
    void on_actionStress_strain_toggled(bool arg1);
    void on_actionAutoscale_triggered();
};
#endif // MAINWINDOW_H
