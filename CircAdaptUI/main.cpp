#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"

int main(int argc, char *argv[])
{

    QFontDatabase::addApplicationFont(":/fonts/LiberationSans-Regular.ttf");
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    CircAdaptUI circadaptui(argc, argv);

    circadaptui.setFont(QFont("Liberation Sans", 11));

    return circadaptui.exec();
}
