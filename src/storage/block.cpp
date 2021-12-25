#include "block.h"

using namespace database;

int BlockReader::GetFileDescriptor() const {
    return this->_fd;
}

off_t BlockReader::GetOriginalOffset() const {
    return this->_offset;
}

int BlockWriter::GetFileDescriptor() const {
    return this->_fd;
}

size_t BlockWriter::Write(char *data, ssize_t len) {
    if (data == nullptr) {
        return -1;
    }

    // We need to normalize to the size of the block!
    char buf[BLOCK_SIZE];
    if (len < BLOCK_SIZE) {
        std::memcpy(buf, data, len);
        for (auto i = len; i < BLOCK_SIZE; i++) {
            buf[i] = 0;
        }
    } else if (len > BLOCK_SIZE) {
        std::memcpy(buf, data, BLOCK_SIZE);
    }

    if (lseek(this->_fd, this->_offset, SEEK_SET) < 0) {
        return -1;
    }

    return write(this->_fd, buf, BLOCK_SIZE);
}