#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"
#include "settings.h"

int main(int argc, char *argv[])
{

    Settings::instance().load("config.json");
    CircAdaptUI circadaptui(argc, argv);

    circadaptui.setFont(QFont(":/CircAdapt/fonts/LiberationSans-Regular.ttf", 10));

    return circadaptui.exec();
}
