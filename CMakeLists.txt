cmake_minimum_required(VERSION 3.5)

project(TelloApp2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS -pthread)

set(SRC main.cpp src/TelloDriver.cpp src/StatusController.cpp src/VideoController.cpp src/Drone.cpp src/CommandController.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

if(ANDROID)
  add_library(TelloApp2 SHARED
    main.cpp
    tellowindow.cpp
    tellowindow.h
    tellowindow.ui
  )
else()
  add_executable(TelloApp2
    main.cpp
    tellowindow.cpp
    tellowindow.h
    tellowindow.ui
    ${SRC}
  )
endif()

target_link_libraries(TelloApp2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})
