# Libuuid supports
find_path(LIBUUID_INCLUDE_DIR uuid.h PATH_SUFFIXES uuid)
find_library(LIBUUID_LIBRARY libuuid.a)

add_subdirectory(storage)
add_subdirectory(port)

# Set up version in project
configure_file(db_config.h.in db_config.h)

add_executable(Database main.cpp)

# Link lib
target_link_libraries(Database PUBLIC
    Storage
    Port
    ${LIBUUID_LIBRARY}
    Threads::Threads
    )

target_include_directories(Database PUBLIC
                            "${DB_BIN_DIR}"
                            "${DB_SRC_DIR}/storage"
                            "${DB_SRC_DIR}/port"
                            )
target_include_directories(Database PRIVATE ${LIBUUID_INCLUDE_DIR})