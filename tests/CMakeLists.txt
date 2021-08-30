include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Storage Raft ${LIBUUID_LIBRARY})
target_include_directories(tests PRIVATE
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_BINARY_DIR}/protos"
                            "${PROJECT_SOURCE_DIR}/storage"
                            "${PROJECT_SOURCE_DIR}/raft"
                            ${LIBUUID_INCLUDE_DIR})

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests)