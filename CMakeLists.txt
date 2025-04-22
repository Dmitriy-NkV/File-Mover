cmake_minimum_required(VERSION 3.16)
project(File-Mover VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(extern/json)
find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)
qt_standard_project_setup(REQUIRES 6.8)

set(SOURCES
    core/file_mover_wrapper.h
    core/file_mover_wrapper.cpp
    core/file_mover.cpp
    core/file_mover.hpp
    core/details/dir.cpp
    core/details/dir.hpp
    core/details/rules.hpp
    core/details/visitors.cpp
    core/details/visitors.hpp
    core/rules_model.h
    core/rules_model.cpp
    core/tray_icon.h
    core/tray_icon.cpp
)

set(QML_FILES
    app/qml/Main.qml
    app/qml/FileManager.qml
    app/qml/DirTaskBar.qml
    app/qml/RuleList.qml
    app/qml/RuleTaskBar.qml
    app/qml/SideMenuButtons.qml
    app/qml/TabBar.qml
)

qt_add_executable(File-Mover
    app/main.cpp
    ${SOURCES}
)

qt_add_qml_module(File-Mover
    URI File-Mover
    VERSION 1.0
    QML_FILES ${QML_FILES}
    SOURCES ${SOURCES}
    RESOURCES app/resources.qrc
)

target_link_libraries(File-Mover
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
    PRIVATE nlohmann_json::nlohmann_json
)

include(GNUInstallDirs)
install(TARGETS File-Mover
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
