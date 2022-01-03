# Fetch the Catch2 test framework
#include(FetchContent)
#FetchContent_Declare(
#  Catch2
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG        v2.13.7
#)
#
#FetchContent_MakeAvailable(Catch2)

# Build the unit test executable
add_executable(UnitTests test.cpp catch.hpp)

# Link in Catch2 + the source libraries
target_link_libraries(UnitTests PRIVATE
        #Catch2::Catch2WithMain
        Port
        Storage
        ${LIBUUID_LIBRARY})

# Link in the src header files
target_include_directories(UnitTests PRIVATE
                            "${DB_BIN_DIR}"
                            "${DB_BIN_DIR}/port"
                            "${DB_BIN_DIR}/storage"
                            "${DB_BIN_DIR}/core"
                            ${LIBUUID_INCLUDE_DIR})

#list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
#include(CTest)
#include(Catch)
#catch_discover_tests(UnitTests)