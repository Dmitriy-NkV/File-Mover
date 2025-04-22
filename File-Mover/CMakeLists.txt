cmake_minimum_required(VERSION 3.16)

project(File-Mover VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appFile-Mover
    main.cpp
)

qt_add_qml_module(appFile-Mover
    URI File-Mover
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES
        QML_FILES DirList.qml
        QML_FILES
        QML_FILES DirTaskBar.qml
        QML_FILES FileManager.qml
        RESOURCES images/file-export.png images/file-import.png images/file-minus.png images/file.png images/pause-button.png images/play-button.png images/setting.png
        QML_FILES RuleList.qml
        SOURCES file_mover_wrapper.h file_mover_wrapper.cpp
        SOURCES ../src/file_mover.cpp ../src/file_mover.hpp
        SOURCES ../src/additionals/json.hpp ../src/details/dir.cpp ../src/details/dir.hpp ../src/details/rules.hpp ../src/details/visitors.cpp ../src/details/visitors.hpp ../src/file_mover.cpp ../src/file_mover.hpp
        QML_FILES TabBar.qml
        QML_FILES SideMenuButtons.qml
        QML_FILES RuleTaskBar.qml
        SOURCES rules_model.h rules_model.cpp
        RESOURCES images/icon.png
        SOURCES tray_icon.h tray_icon.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFile-Mover PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFile-Mover
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFile-Mover
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appFile-Mover
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
