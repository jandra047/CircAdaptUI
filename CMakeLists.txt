cmake_minimum_required(VERSION 3.16)
project(CircAdaptUI VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui OpenGL Svg SvgWidgets)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS PrintSupport Widgets)

enable_testing()
add_subdirectory(tests)



list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(CHECK_START "Fetching CircAdapt_Library")
include(FetchContent)
FetchContent_Declare(
  CircAdapt_Library
  GIT_REPOSITORY git@gitlab.maastrichtuniversity.nl:circadapt/CircAdapt_Library.git
  GIT_TAG be5d38355eb02e9cfc9009199496b5b8563d07e1
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(CircAdapt_Library)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "CircAdapt_Library fetched")

list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(CHECK_START "Fetching QtPropertyBrowser")
FetchContent_Declare(
  QtPropertyBrowser
  GIT_REPOSITORY git@gitlab.maastrichtuniversity.nl:P70074313/qtpropertybrowser.git
  GIT_TAG 5f57e3b1f47515fedacabeb7a0da0433e29cf597
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(QtPropertyBrowser)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "QtPropertyBrowser fetched")

list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(CHECK_START "Fetching CircAdapt_Oxygen")
FetchContent_Declare(
  CircAdapt_Oxygen
  GIT_REPOSITORY git@gitlab.maastrichtuniversity.nl:circadapt/circadapt_oxygen.git
  GIT_TAG 38e04f87e46f4d3b2ef2b807e98b6f7fd58db056
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(CircAdapt_Oxygen)
list(POP_BACK CMAKE_MESSAGE_INDENT)
message(CHECK_PASS "CircAdapt_Oxygen fetched")

qt_standard_project_setup()

qt_add_executable(CircAdaptUI WIN32 MACOSX_BUNDLE
    CircAdaptUI/main.cpp
    CircAdaptUI/circadaptui.cpp CircAdaptUI/circadaptui.h
    CircAdaptUI/buffer.cpp CircAdaptUI/buffer.h
    CircAdaptUI/graphcontainer.cpp CircAdaptUI/graphcontainer.h
    CircAdaptUI/Widgets/graphgrid.cpp CircAdaptUI/Widgets/graphgrid.h
    CircAdaptUI/Graphs/loopgraph.cpp CircAdaptUI/Graphs/loopgraph.h
    CircAdaptUI/Signals/loopsignal.cpp CircAdaptUI/Signals/loopsignal.h
    CircAdaptUI/mainwindow.cpp CircAdaptUI/mainwindow.h CircAdaptUI/mainwindow.ui
    CircAdaptUI/modelwrapper.cpp CircAdaptUI/modelwrapper.h
    CircAdaptUI/settings.cpp CircAdaptUI/settings.h
    CircAdaptUI/Graphs/signalgraph.cpp CircAdaptUI/Graphs/signalgraph.h
    CircAdaptUI/Signals/timesignal.cpp CircAdaptUI/Signals/timesignal.h
    dependencies/qcustomplot.cpp dependencies/qcustomplot.h
    CircAdaptUI/circadaptui.h CircAdaptUI/circadaptui.cpp
    CircAdaptUI/datacontainer.h CircAdaptUI/datacontainer.cpp
    CircAdaptUI/mainwindow.ui
    CircAdaptUI/Widgets/valueview.h CircAdaptUI/Widgets/valueview.cpp
    CircAdaptUI/beatdata.h CircAdaptUI/beatdata.cpp
    CircAdaptUI/Widgets/paramviewdockwidget.h CircAdaptUI/Widgets/paramviewdockwidget.cpp CircAdaptUI/Widgets/paramviewdockwidget.ui
    CircAdaptUI/PropertyBrowser/propertybrowserbase.h CircAdaptUI/PropertyBrowser/propertybrowserbase.cpp
    CircAdaptUI/PropertyBrowser/systempropertybrowser.h CircAdaptUI/PropertyBrowser/systempropertybrowser.cpp
    CircAdaptUI/PropertyBrowser/customeditorfactory.h CircAdaptUI/PropertyBrowser/customeditorfactory.cpp
    CircAdaptUI/Widgets/modelgraphicsview.h CircAdaptUI/Widgets/modelgraphicsview.cpp


    CircAdaptUI/linemarker.h CircAdaptUI/linemarker.cpp
    Resources/resources.qrc
    CircAdaptUI/SVGviews/svgobjectbase.h CircAdaptUI/SVGviews/svgobjectbase.cpp
    CircAdaptUI/SVGviews/svgtorsoobject.h CircAdaptUI/SVGviews/svgtorsoobject.cpp

    CircAdaptUI/Widgets/graphicwidget.h CircAdaptUI/Widgets/graphicwidget.cpp
    CircAdaptUI/Widgets/viewtypes.h
    CircAdaptUI/SVGviews/svgheartobject.h CircAdaptUI/SVGviews/svgheartobject.cpp
    CircAdaptUI/SVGviews/svgtissueobject.h CircAdaptUI/SVGviews/svgtissueobject.cpp
    CircAdaptUI/SVGviews/togglebuttongroup.h CircAdaptUI/SVGviews/togglebuttongroup.cpp
    CircAdaptUI/SVGviews/DrawingElements/graphicelement.h CircAdaptUI/SVGviews/DrawingElements/graphicelement.cpp
    CircAdaptUI/SVGviews/DrawingElements/valveelement.h CircAdaptUI/SVGviews/DrawingElements/valveelement.cpp
    CircAdaptUI/SVGviews/DrawingElements/shuntelement.h CircAdaptUI/SVGviews/DrawingElements/shuntelement.cpp
    CircAdaptUI/SVGviews/DrawingElements/rightatrium.h CircAdaptUI/SVGviews/DrawingElements/rightatrium.cpp
    CircAdaptUI/SVGviews/DrawingElements/leftatrium.h CircAdaptUI/SVGviews/DrawingElements/leftatrium.cpp
    CircAdaptUI/SVGviews/DrawingElements/rightventricle.h CircAdaptUI/SVGviews/DrawingElements/rightventricle.cpp
    CircAdaptUI/SVGviews/DrawingElements/septum.h CircAdaptUI/SVGviews/DrawingElements/septum.cpp
    CircAdaptUI/SVGviews/DrawingElements/leftventricle.h CircAdaptUI/SVGviews/DrawingElements/leftventricle.cpp
    CircAdaptUI/loopmarker.h CircAdaptUI/loopmarker.cpp
    CircAdaptUI/SVGviews/drawingelementgroup.h CircAdaptUI/SVGviews/drawingelementgroup.cpp
    CircAdaptUI/PropertyBrowser/custompropertymanager.h CircAdaptUI/PropertyBrowser/custompropertymanager.cpp
    CircAdaptUI/PropertyBrowser/resetbutton.h CircAdaptUI/PropertyBrowser/resetbutton.cpp
    CircAdaptUI/Graphs/mmode.h CircAdaptUI/Graphs/mmode.cpp
    CircAdaptUI/SVGviews/DrawingElements/textcircle.h CircAdaptUI/SVGviews/DrawingElements/textcircle.cpp
    CircAdaptUI/SVGviews/DrawingElements/leftventricle2.h CircAdaptUI/SVGviews/DrawingElements/leftventricle2.cpp

)

qt_add_resources(CircAdaptUI
    Resources/resources.qrc
    PREFIX "/")

target_compile_definitions(CircAdaptUI PRIVATE
    QCUSTOMPLOT_USE_OPENGL
)

target_link_libraries(CircAdaptUI PRIVATE
    Qt::Core
    Qt::Gui
    Qt::OpenGL
    Qt::Svg
    Qt::SvgWidgets
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
elseif(APPLE)
    add_subdirectory(macos)
    target_link_libraries(CircAdaptUI PRIVATE "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
    target_link_libraries(CircAdaptUI PRIVATE macOSHelpers)
endif()



target_link_libraries(CircAdaptUI PRIVATE
    CircAdaptLib
    qtpropertybrowser
    Oxygen
)
include_directories("dependencies")
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
