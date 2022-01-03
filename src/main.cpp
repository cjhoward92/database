#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>
#include <string>

#include "block.h"
#include "db_config.h"
#include "port/port.h"
#include "core/db.h"

using namespace database;

void CreateDb() {
    std::filesystem::path dbPath("/tmp/database");
    Db db;
    db.Init(dbPath);
}

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Version: " << Database_VERSION_MAJOR << "." << Database_VERSION_MINOR << std::endl;

    const char *filename = "/tmp/test-db";
    int fd = open(filename, O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
        std::cerr << "Error: " << fd << std::endl;
        return -1;
    }
    close(fd);

    std::cout << "Found file: " << filename << std::endl;

    uintmax_t fsz = std::filesystem::file_size(filename);
    std::cout << "File size: " << fsz << std::endl;

    File file(filename);

    BlockWriter writer(&file, 0);
    BlockWriter writer2(&file, BLOCK_SIZE);

    char buf[5000];
    for (int i = 0; i < 5000; i++) {
        buf[i] = (char)((i % 93) + 33);
    }

    writer.Write(buf, 1024);
    writer2.Write(buf, 1024);

    fsz = std::filesystem::file_size(filename);
    std::cout << "File size: " << fsz << std::endl;

    BlockReader reader(&file, 0);

    char readBuffer[BLOCK_SIZE];

    reader.Read(readBuffer, BLOCK_SIZE);

    std::cout << "Buffer: ";
    for (char i : readBuffer) {
        std::cout << i;
    }
    std::cout << std::endl;

    unlink(filename);

    CreateDb();

    return 0;
}