#include <QApplication>
#include <QFontDatabase>
#include "circadaptui.h"

#ifdef __APPLE__
#include "helpers.h"
#endif

int main(int argc, char *argv[])
{

    QFontDatabase::addApplicationFont(":/fonts/LiberationSans-Regular.ttf");

    QFont font = QFont("Liberation Sans", 11);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setHintingPreference(QFont::PreferNoHinting);
    QApplication::setFont(font);

    CircAdaptUI circadaptui(argc, argv);

#ifdef __APPLE__
    setAquaAppearance();
#elif defined _WIN32 || defined __WIN64
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");
#endif
    return circadaptui.exec();
}
