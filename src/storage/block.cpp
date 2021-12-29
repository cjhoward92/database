#include "block.h"

#include <cstring>

using namespace database;

ssize_t BlockReader::Read(char *buf, size_t length) {
    return this->_file->Read(buf, length, this->_offset);
}

size_t BlockWriter::Write(char *data, size_t len) {
    if (data == nullptr || len < 1) {
        throw std::invalid_argument("A buffer is required and len must be greater than 0.");
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

    return this->_file->Write(buf, BLOCK_SIZE, this->_offset);
}