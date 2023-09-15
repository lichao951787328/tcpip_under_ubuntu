cmake_minimum_required(VERSION 3.2)
project(server)
find_package(glog REQUIRED)
include_directories(
    ./
    ${glog_INCLUDE_DIRS}
)
add_compile_options(-Wall -lpthread)
add_executable(server tcpip_port.cpp main.cpp)
# target_link_directories(client glog::glog)
target_link_libraries(server glog::glog)