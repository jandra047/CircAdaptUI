#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"

int main(int argc, char *argv[])
{

    QFontDatabase::addApplicationFont(":/fonts/LiberationSans-Regular.ttf");
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QFont font = QFont("Liberation Sans", 11);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::PreferNoHinting);
    QApplication::setFont(font);

    CircAdaptUI circadaptui(argc, argv);


    return circadaptui.exec();
}
