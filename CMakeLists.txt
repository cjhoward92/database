cmake_minimum_required(VERSION 3.21.1)

# Set project name
project(Database VERSION 0.1 LANGUAGES C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(DB_BIN_DIR "${PROJECT_BINARY_DIR}/src")
set(DB_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(tests)