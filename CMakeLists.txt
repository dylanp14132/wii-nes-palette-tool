cmake_minimum_required(VERSION 3.19)
project(Wii-NES-VC-Color-Palette-Patcher LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Wii-NES-VC-Color-Palette-Patcher
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(Wii-NES-VC-Color-Palette-Patcher
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Wii-NES-VC-Color-Palette-Patcher
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Wii-NES-VC-Color-Palette-Patcher
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
