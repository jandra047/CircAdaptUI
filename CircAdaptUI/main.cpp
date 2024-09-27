#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"

int main(int argc, char *argv[])
{

    QFontDatabase::addApplicationFont(":/fonts/LiberationSans-Regular.ttf");
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    CircAdaptUI circadaptui(argc, argv);

    QFont font = QFont("Liberation Sans", 11);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::PreferNoHinting);

    circadaptui.setFont(font);

    return circadaptui.exec();
}
