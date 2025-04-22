cmake_minimum_required(VERSION 3.16)

project(File-Mover VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/json)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(File-Mover
    main.cpp
)

qt_add_resources(File-Mover "app_resources"
    PREFIX "/images/"
    FILES
        resources.qrc
        images/icon.png
        images/file-export.png
        images/file-import.png
        images/file-minus.png
        images/file.png
        images/setting.png
        images/play-button.png
        images/pause-button.png

    PREFIX "/"
    FILES
        resources.qrc
        Main.qml
        DirList.qml
        DirTaskBar.qml
        FileManager.qml
        RuleList.qml
        TabBar.qml
        SideMenuButtons.qml
        RuleTaskBar.qml
)

set(QML_FILES
    Main.qml
    DirList.qml
    DirTaskBar.qml
    FileManager.qml
    RuleList.qml
    TabBar.qml
    SideMenuButtons.qml
    RuleTaskBar.qml
)

set(SOURCES
    file_mover_wrapper.h
    file_mover_wrapper.cpp
    src/file_mover.cpp
    src/file_mover.hpp
    src/details/dir.cpp
    src/details/dir.hpp
    src/details/rules.hpp
    src/details/visitors.cpp
    src/details/visitors.hpp
    rules_model.h
    rules_model.cpp
    tray_icon.h
    tray_icon.cpp
)

set(RESOURCES
    images/file-export.png
    images/file-import.png
    images/file-minus.png
    images/file.png
    images/pause-button.png
    images/play-button.png
    images/setting.png
    images/icon.png
)

qt_add_qml_module(File-Mover
    URI File-Mover
    VERSION 1.0
    QML_FILES ${QML_FILES}
    SOURCES ${SOURCES}
    RESOURCES ${RESOURCES}
    RESOURCES resources.qrc
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
