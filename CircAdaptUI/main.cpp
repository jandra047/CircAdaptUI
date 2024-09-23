#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"

int main(int argc, char *argv[])
{

    QFontDatabase::addApplicationFont(":/fonts/LiberationSans-Regular.ttf");

    CircAdaptUI circadaptui(argc, argv);

    circadaptui.setFont(QFont("Liberation Sans"));

    return circadaptui.exec();
}
