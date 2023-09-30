cmake_minimum_required(VERSION 3.5)

project(UAVSwarmSimulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_definitions(-DSHOWMAPPOINTS)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
        main.cpp
        src/UAVSwarmSimulator.cpp
        src/SelectMapDialog.cpp
        src/AddNewUAVDialog.cpp
        src/AddNewThreatDialog.cpp
        src/ManageSwarmDialog.cpp
        src/ManageMissionDialog.cpp
        src/Definitions.cpp
        src/SimItem.cpp
        src/UAV.cpp
        src/Threat.cpp
        src/Mission.cpp
        src/Viewer.cpp
        src/Scene.cpp
        include/UAVSwarmSimulator.h
        include/SelectMapDialog.h
        include/AddNewUAVDialog.h
        include/AddNewThreatDialog.h
        include/ManageSwarmDialog.h
        include/ManageMissionDialog.h
        include/Definitions.h
        include/SimItem.h
        include/UAV.h
        include/Threat.h
        include/Mission.h
        include/Viewer.h
        include/Scene.h
        ui/UAVSwarmSimulator.ui
        ui/SelectMapDialog.ui
        ui/AddNewUAVDialog.ui
        ui/AddNewThreatDialog.ui
        ui/ManageSwarmDialog.ui
        ui/ManageMissionDialog.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UAVSwarmSimulator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET UAVSwarmSimulator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(UAVSwarmSimulator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(UAVSwarmSimulator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(UAVSwarmSimulator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(UAVSwarmSimulator PRIVATE Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(UAVSwarmSimulator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS UAVSwarmSimulator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UAVSwarmSimulator)
endif()
