# Prepare gRPC
# TODO(carson) Re-add gRPC when necessary
# include(./grpc.cmake)
# option(USE_SYSTEM_GRPC "Use system installed gRPC" OFF)
# if(USE_SYSTEM_GRPC)
#   # This branch assumes that gRPC and all its dependencies are already installed
#   # on this system, so they can be located by find_package().

#   # Find Protobuf installation
#   # Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
#   set(protobuf_MODULE_COMPATIBLE TRUE)
#   find_package(Protobuf CONFIG REQUIRED)
#   message(STATUS "Using protobuf ${Protobuf_VERSION}")

#   set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
#   set(_REFLECTION gRPC::grpc++_reflection)
#   if(CMAKE_CROSSCOMPILING)
#     find_program(_PROTOBUF_PROTOC protoc)
#   else()
#     set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
#   endif()

#   # Find gRPC installation
#   # Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
#   find_package(gRPC CONFIG REQUIRED)
#   message(STATUS "Using gRPC ${gRPC_VERSION}")

#   set(_GRPC_GRPCPP gRPC::grpc++)
#   if(CMAKE_CROSSCOMPILING)
#     find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
#   else()
#     set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
#   endif()
# else()
#   # Build gRPC using FetchContent or add_subdirectory
#   include(FetchContent)
#   FetchContent_Declare(
#     gRPC
#     GIT_REPOSITORY https://github.com/grpc/grpc
#     GIT_TAG        v1.38.0
#   )
#   set(FETCHCONTENT_QUIET OFF)
#   FetchContent_MakeAvailable(gRPC)

#   # Since FetchContent uses add_subdirectory under the hood, we can use
#   # the grpc targets directly from this build.
#   set(_PROTOBUF_LIBPROTOBUF libprotobuf)
#   set(_REFLECTION grpc++_reflection)
#   set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
#   set(_GRPC_GRPCPP grpc++)
#   if(CMAKE_CROSSCOMPILING)
#     find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
#   else()
#     set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
#   endif()
# endif()

# Libuuid supports
find_path(LIBUUID_INCLUDE_DIR uuid.h PATH_SUFFIXES uuid)
find_library(LIBUUID_LIBRARY libuuid.a)

# Add subdirs with nested cmake files
# TODO(carson) Add protos when necessary
# add_subdirectory(protos)
add_subdirectory(raft)
add_subdirectory(storage)

# Set up version in project
configure_file(db_config.h.in db_config.h)

add_executable(Database main.cpp)

# Link lib
target_link_libraries(Database PUBLIC
  Storage
  Raft
  # ${_GRPC_GRPCPP}
  # ${DATABASE_PROTO}
  ${LIBUUID_LIBRARY}
  Threads::Threads
  )

target_include_directories(Database PUBLIC
                           "${DB_BIN_DIR}"
                           # "${DB_BIN_DIR}/protos"
                           "${DB_SRC_DIR}/storage"
                           "${DB_SRC_DIR}/raft"
                           )
target_include_directories(Database PRIVATE ${LIBUUID_INCLUDE_DIR})