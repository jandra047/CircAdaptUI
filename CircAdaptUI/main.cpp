#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"

int main(int argc, char *argv[])
{

    CircAdaptUI circadaptui(argc, argv);

    circadaptui.setFont(QFont(":/CircAdapt/fonts/LiberationSans-Regular.ttf", 10));

    return circadaptui.exec();
}
