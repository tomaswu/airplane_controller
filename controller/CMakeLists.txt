cmake_minimum_required(VERSION 3.16)

project(airplane_controller VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Network Bluetooth Widgets)

qt_policy(SET QTP0001 NEW)

qt_standard_project_setup()

qt_add_resources(qrcs resources.qrc)

file(GLOB CXXSOURCES srcs/*.h srcs/*.cpp)
message(${CXXSOURCES})

qt_add_executable(appairplane_controller
    ${CXXSOURCES}
    ${qrcs}
)

qt_add_qml_module(appairplane_controller
    URI airplane_controller
    VERSION 1.0
    QML_FILES srcs/Main.qml
    QML_FILES srcs/ControllerUi.qml
    QML_FILES srcs/DirectionControl.qml
    QML_FILES srcs/ArrowButton.qml
    QML_FILES srcs/ColorImage.qml
    QML_FILES srcs/Battery.qml
    SOURCES srcs/control.h srcs/control.cpp
    SOURCES srcs/tprocotol.h srcs/tprocotol.cpp
)

set(QML_IMPORT_PATH imports)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appairplane_controller PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appairplane_controller
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appairplane_controller
    PRIVATE Qt6::Quick Qt6::Network Qt6::Bluetooth Qt6::Widgets
)

if (APPLE)
    # Using absolute path for shared plist files is a Ninja bug workaround
    get_filename_component(SHARED_PLIST_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
    message(${SHARED_PLIST_DIR})
    if (IOS)
        set_target_properties(appairplane_controller PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST "${SHARED_PLIST_DIR}/Info.cmake.ios.plist"
        )
    else()
        set_target_properties(appairplane_controller PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST "${SHARED_PLIST_DIR}/Info.cmake.macos.plist"
        )
    endif()
endif()

# if(ANDROID)
#     set_target_properties(appairplane_controller PROPERTIES
#         MACOSX_BUNDLE_INFO_PLIST "${SHARED_PLIST_DIR}/Info.cmake.ios.plist"
#     )

# endif()


include(GNUInstallDirs)
install(TARGETS appairplane_controller
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
