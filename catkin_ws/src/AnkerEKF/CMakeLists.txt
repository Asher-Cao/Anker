cmake_minimum_required(VERSION 2.8.3)
project(anker_ekf_pro)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
#-DEIGEN_USE_MKL_ALL")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    geometry_msgs
    nav_msgs
    tf
    cv_bridge
    std_msgs
    message_generation
    )

find_package(OpenCV REQUIRED)

message(WARNING "OpenCV_VERSION: ${OpenCV_VERSION}")

find_package(Ceres REQUIRED)

include_directories(${catkin_INCLUDE_DIRS} ${CERES_INCLUDE_DIRS})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Eigen3)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  src
)

add_message_files(
  FILES
  AnkerDataType.msg
)
generate_messages(
    DEPENDENCIES
    std_msgs
)
catkin_package(
    CATKIN_DEPENDS
    message_runtime
    )

add_executable(anker_ekf
    src/main.cpp
    src/anker.cpp
    )


target_link_libraries(anker_ekf ${catkin_LIBRARIES} ${OpenCV_LIBS} ${CERES_LIBRARIES})



