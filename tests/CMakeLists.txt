# Fetch the Catch2 test framework
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

# Build the unit test executable
add_executable(UnitTests test.cpp)

# Link in Catch2 + the source libraries
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain Storage Raft ${LIBUUID_LIBRARY})

# Link in the src header files
target_include_directories(UnitTests PRIVATE
                            "${DB_BIN_DIR}"
                            "${DB_BIN_DIR}/protos"
                            "${DB_SRC_DIR}/storage"
                            "${DB_SRC_DIR}/raft"
                            ${LIBUUID_INCLUDE_DIR})

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(UnitTests)