cmake_minimum_required(VERSION 3.17)
project(Tello_Drone_Controller)

set(CMAKE_CXX_STANDARD 20)
set(SRC main.cpp src/tello_driver.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)

add_executable(${PROJECT_NAME} ${SRC})