cmake_minimum_required(VERSION 3.2)
project(client)
find_package(glog REQUIRED)
include_directories(
    ./
    ${glog_INCLUDE_DIRS}
)
add_compile_options(-Wall -lpthread)
add_executable(client tcpip_port.cpp main.cpp)
# target_link_directories(client glog::glog)
target_link_libraries(client glog::glog)