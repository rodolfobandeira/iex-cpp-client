cmake_minimum_required(VERSION 3.1)

project(iex CXX)
set(CMAKE_CXX_STANDARD 11)

# Unfortunately there's no FindJsoncpp.cmake file, so we have to do this clunky
# two-liner instead to find the jsoncpp package:
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})
link_libraries(${JSONCPP_LIBRARIES})

# Find CURL
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
link_libraries(${CURL_LIBRARIES})

add_executable(main main.cpp)
