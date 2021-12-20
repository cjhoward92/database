#include "block.h"

using namespace database;

int BlockReader::GetFileDescriptor() const {
    return this->_fd;
}

off_t BlockReader::GetOriginalOffset() const {
    return this->_offset;
}