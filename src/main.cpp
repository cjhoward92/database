#include <iostream>
#include <compare>
#include <filesystem>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "storage.h"
#include "block.h"
#include "db_config.h"

using namespace database;

int main() {
    std::cout << "Hello world!" << std::endl;
    std::cout << "Version: " << Database_VERSION_MAJOR << "." << Database_VERSION_MINOR << std::endl;

    char *filename = "/tmp/test-db";
    int fd = open(filename, O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
        std::cerr << "Error: " << fd << std::endl;
        return -1;
    }

    std::cout << "Found file: " << filename << std::endl;

    uintmax_t fsz = file_len(filename);
    std::cout << "File size: " << fsz << std::endl;

    BlockWriter writer(fd, 0);
    BlockWriter writer2(fd, BLOCK_SIZE);

    char buf[5000];
    for (int i = 0; i < 5000; i++) {
        buf[i] = (char)((i % 93) + 33);
    }

    writer.Write(buf, 1024);
    writer2.Write(buf, 1024);

    fsz = file_len(filename);
    std::cout << "File size: " << fsz << std::endl;

    close(fd);
    unlink(filename);

    return 0;
}