#ifndef CIRCADAPTUI_H
#define CIRCADAPTUI_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"

class CircAdaptUI : public QApplication
{
public:
    CircAdaptUI(int &argc, char **argv);
    ~CircAdaptUI();

private:
    MainWindow* m_mainwindow = Q_NULLPTR;
    QTimer *m_timer = new QTimer(this);
    Buffer m_buffer{};
    ModelWrapper m_mw;

private slots:
    void togglePlay(bool isOn);
};

#endif // CIRCADAPTUI_H
