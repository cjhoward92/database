# Database

The start of a simple database in C++

## Building & Setup

The following document how to build and set up the project.

### Build Pre-requisites

[gRPC pre-reqs](https://github.com/grpc/grpc/blob/master/BUILDING.md#pre-requisites)

More on [gRPC here](https://github.com/grpc/grpc/tree/master/src/cpp#to-start-using-grpc-c) and [here](https://grpc.io/docs/languages/cpp/quickstart/)

### Building

Make sure you have at least `cmake` version `3.21.1` installed. Create a build folder:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

Build the executable:

```bash
cmake --build .
```

Done!

If you want to build in debug mode, simply change the build type
from `Release` to `Debug` when configuring cmake.

## Tutorials

[Cmake](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html)
[gRPC C++](https://github.com/grpc/grpc/blob/v1.38.0/examples/cpp/route_guide/route_guide_client.cc)
