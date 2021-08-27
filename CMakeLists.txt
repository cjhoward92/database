cmake_minimum_required(VERSION 3.21.1)

# Set project name
project(Database VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add lib subdir
add_subdirectory(storage)

# Set up version in project
configure_file(db_config.h.in db_config.h)

add_executable(Database main.cpp)

# Link lib
target_link_libraries(Database PUBLIC Storage)

target_include_directories(Database PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/storage"
                           )