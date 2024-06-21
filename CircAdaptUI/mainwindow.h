#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include "modelwrapper.h"
#include "buffer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ModelWrapper& mw, Buffer& buffer, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Buffer& buffer;
    ModelWrapper& mw;
    QLabel* l = Q_NULLPTR;

public: signals:
    void updateDone();
    void togglePlay(bool isPlay);

public slots:
    void updateGraphs();
    void updateBufferLenText()
    {
        l->setText("Buffer size: " + QString::number(buffer.getLen()));
    }

};
#endif // MAINWINDOW_H
