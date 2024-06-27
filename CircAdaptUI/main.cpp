#include <QApplication>
#include "circadaptui.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    Settings::instance().load("config.json");
    CircAdaptUI circadaptui(argc, argv);

    return circadaptui.exec();
}
