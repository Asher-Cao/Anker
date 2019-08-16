cmake_minimum_required(VERSION 2.8.3)
project(anker_data_publish)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
#-DEIGEN_USE_MKL_ALL")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    tf
    message_generation
    )


include_directories(${catkin_INCLUDE_DIRS} src)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


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
add_executable(anker_data_publisher
    src/AnkerDatasPublisher.cpp
    src/readankerdatafile.cpp
 
    )


target_link_libraries(anker_data_publisher ${catkin_LIBRARIES})



