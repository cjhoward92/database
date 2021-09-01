# Proto file
get_filename_component(Protos "./route_guide.proto" ABSOLUTE)
get_filename_component(ProtosPath "${Protos}" PATH)

# Generated sources
set(ProtosSrc "${CMAKE_CURRENT_BINARY_DIR}/route_guide.pb.cc")
set(ProtosHdrs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.pb.h")
set(GrpcProtoSrc "${CMAKE_CURRENT_BINARY_DIR}/route_guide.grpc.pb.cc")
set(GrpcProtoHdrs "${CMAKE_CURRENT_BINARY_DIR}/route_guide.grpc.pb.h")
add_custom_command(
  OUTPUT "${ProtosSrc}" "${ProtosHdrs}" "${GrpcProtoSrc}" "${GrpcProtoHdrs}"
  COMMAND ${_PROTOBUF_PROTOC}
  ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
    --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
    -I "${ProtosPath}"
    --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
    "${Protos}"
  DEPENDS "${Protos}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(GrpcProtos
  ${ProtosSrc}
  ${ProtosHdrs}
  ${GrpcProtoSrc}
  ${GrpcProtoHdrs})

target_link_libraries(GrpcProtos
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

set(DATABASE_PROTO GrpcProtos PARENT_SCOPE)