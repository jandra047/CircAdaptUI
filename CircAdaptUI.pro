QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
DEFINES += QCUSTOMPLOT_USE_OPENGL
CONFIG += c++17
# CONFIG += sanitizer sanitize_address

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buffer.cpp \
    graphgrid.cpp \
    loopsignal.cpp \
    pvloopgraph.cpp \
    qcustomplot.cpp \
    graphcontainer.cpp \
    main.cpp \
    mainwindow.cpp \
    modelwrapper.cpp \
    signalgraph.cpp \
    timesignal.cpp

HEADERS += \
    buffer.h \
    graphgrid.h \
    loopsignal.h \
    pvloopgraph.h \
    qcustomplot.h \
    graphcontainer.h \
    mainwindow.h \
    modelwrapper.h \
    signalgraph.h \
    timesignal.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CircAdapt/gitlab/CircAdapt_Library/build/release/ -lCircAdaptLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CircAdapt/gitlab/CircAdapt_Library/build/debug/ -lCircAdaptLib
else:unix: LIBS += -L$$PWD/../../CircAdapt/gitlab/CircAdapt_Library/build/ -lCircAdaptLib

INCLUDEPATH += $$PWD/../../CircAdapt/gitlab/CircAdapt_Library/include
DEPENDPATH += $$PWD/../../CircAdapt/gitlab/CircAdapt_Library/include
