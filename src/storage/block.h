#ifndef __BLOCK__
#define __BLOCK__

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

namespace database {

// Defines the block file format for the db

#define BLOCK_SIZE 4096

class BlockReader {
public:
    explicit BlockReader(int fd, off_t offset): _fd(fd), _offset(offset) {}
    ~BlockReader() {}

    int GetFileDescriptor() const;
    off_t GetOriginalOffset() const;

private:
    int _fd;
    off_t _offset;
};

class BlockWriter {
public:
    explicit BlockWriter(int fd, off_t offset): _fd(fd), _offset(offset) {}
    ~BlockWriter() {}

    int GetFileDescriptor() const;
    size_t Write(char *data, ssize_t len);

private:
    int _fd;
    off_t _offset;
};

} // end namespace

#endif