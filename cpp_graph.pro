QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
# CONFIG += sanitizer sanitize_address

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../CircAdapt_cpp/qcustomplot.cpp \
    graphcontainer.cpp \
    main.cpp \
    mainwindow.cpp \
    signal.cpp

HEADERS += \
    ../CircAdapt_cpp/qcustomplot.h \
    graphcontainer.h \
    mainwindow.h \
    signal.h

FORMS += \
    mainwindow.ui

# QMAKE_CXXFLAGS += -Werror -w -fsanitize=address -g
# QMAKE_LFLAGS_DEBUG += -fsanitize=address
# QMAKE_CXXFLAGS+="-fsanitize=address -fno-omit-frame-pointer"

# QMAKE_CFLAGS+="-fsanitize=address -fno-omit-frame-pointer"

# QMAKE_LFLAGS+="-fsanitize=address"
# DEFINES += QCUSTOMPLOT_USE_OPENGL

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
