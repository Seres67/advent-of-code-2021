project(common)

set(CMAKE_CXX_STANDARD 20)

add_library(common src/Utils.cpp include/Utils.hpp)
target_include_directories(common PUBLIC include)