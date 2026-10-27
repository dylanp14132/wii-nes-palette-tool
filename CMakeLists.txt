cmake_minimum_required(VERSION 3.19)
project(wii-nes-palette-tool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

include_directories(
    src 
    include
)

qt_add_executable(wii-nes-palette-tool
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp include/mainwindow.h ui/mainwindow.ui
    src/helper.cpp include/helper.h
    images.qrc
)

target_link_libraries(wii-nes-palette-tool
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS wii-nes-palette-tool
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET wii-nes-palette-tool
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
