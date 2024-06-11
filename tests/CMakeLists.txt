project(test LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Test Widgets)

qt_standard_project_setup()

# Add test executable
qt_add_executable(TestBuffer test_Buffer.cpp ../CircAdaptUI/buffer.h ../CircAdaptUI/buffer.cpp)
qt_add_executable(TestWrapper test_Wrapper.cpp
    ../CircAdaptUI/modelwrapper.h
    ../CircAdaptUI/modelwrapper.cpp
    ../CircAdaptUI/buffer.h
    ../CircAdaptUI/buffer.cpp
    ../CircAdaptUI/settings.h
    ../CircAdaptUI/settings.cpp)
include_directories(../CircAdaptUI)

# Link the test executable with Qt5 Test
target_link_libraries(TestBuffer PRIVATE Qt6::Test)
target_link_libraries(TestWrapper PRIVATE Qt6::Test CircAdaptLib)

# Add tests
add_test(NAME TestBuffer COMMAND TestBuffer)
add_test(NAME TestWrapper COMMAND TestWrapper)
