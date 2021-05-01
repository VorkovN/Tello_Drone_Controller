cmake_minimum_required(VERSION 3.17)
project(Tello_Drone_Controller)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -pthread)

set(SRC main.cpp
        src/TelloDriver.cpp
        src/StatusController.cpp
        src/VideoController.cpp
        src/Drone.cpp
        src/CommandController.cpp
        src/DroneWindow.cpp)

find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)

add_executable(${PROJECT_NAME} ${SRC})


find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} Qt5::Widgets)
