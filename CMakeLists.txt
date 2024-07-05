cmake_minimum_required(VERSION 3.16)
project(CircAdaptUI VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui OpenGL)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS PrintSupport Widgets)

enable_testing()
add_subdirectory(tests)


list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(CHECK_START "Fetching CircAdapt_Library")
include(FetchContent)
FetchContent_Declare(
  CircAdapt_Library
  GIT_REPOSITORY git@gitlab.maastrichtuniversity.nl:circadapt/CircAdapt_Library.git
  GIT_TAG fca151827ba9248058c0c708039bde6610ed8933
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(CircAdapt_Library)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "CircAdapt_Library fetched")

list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(CHECK_START "Fetching QtPropertyBrowser")
include(FetchContent)
FetchContent_Declare(
  QtPropertyBrowser
  GIT_REPOSITORY git@gitlab.maastrichtuniversity.nl:P70074313/qtpropertybrowser.git
  GIT_TAG 9bb78923ff94ec148982e993806a22b1140b4844
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(QtPropertyBrowser)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "QtPropertyBrowser fetched")

qt_standard_project_setup()

qt_add_executable(CircAdaptUI WIN32 MACOSX_BUNDLE
    CircAdaptUI/main.cpp
    CircAdaptUI/circadaptui.cpp CircAdaptUI/circadaptui.h
    CircAdaptUI/buffer.cpp CircAdaptUI/buffer.h
    CircAdaptUI/graphcontainer.cpp CircAdaptUI/graphcontainer.h
    CircAdaptUI/graphgrid.cpp CircAdaptUI/graphgrid.h
    CircAdaptUI/loopgraph.cpp CircAdaptUI/loopgraph.h
    CircAdaptUI/loopsignal.cpp CircAdaptUI/loopsignal.h
    CircAdaptUI/mainwindow.cpp CircAdaptUI/mainwindow.h CircAdaptUI/mainwindow.ui
    CircAdaptUI/modelwrapper.cpp CircAdaptUI/modelwrapper.h
    CircAdaptUI/settings.cpp CircAdaptUI/settings.h
    CircAdaptUI/signalgraph.cpp CircAdaptUI/signalgraph.h
    CircAdaptUI/timesignal.cpp CircAdaptUI/timesignal.h
    dependencies/qcustomplot.cpp dependencies/qcustomplot.h
    CircAdaptUI/circadaptui.h CircAdaptUI/circadaptui.cpp
    CircAdaptUI/datacontainer.h
    CircAdaptUI/mainwindow.ui
    CircAdaptUI/valueview.h CircAdaptUI/valueview.cpp
    CircAdaptUI/beatdata.h CircAdaptUI/beatdata.cpp
)

target_compile_definitions(CircAdaptUI PRIVATE
    QCUSTOMPLOT_USE_OPENGL
)

target_link_libraries(CircAdaptUI PRIVATE
    Qt::Core
    Qt::Gui
    Qt::OpenGL
)

if(${QT_VERSION_MAJOR} GREATER 4)
    target_link_libraries(CircAdaptUI PRIVATE
        Qt::PrintSupport
        Qt::Widgets
    )
endif()

if (WIN32)
    target_link_libraries(CircAdaptUI PRIVATE
        OpenGL32)
endif()

target_link_libraries(CircAdaptUI PRIVATE
    CircAdaptLib
    qtpropertybrowser
)

add_dependencies(CircAdaptUI CircAdaptLib qtpropertybrowser)

install(TARGETS CircAdaptUI
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET CircAdaptUI
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
