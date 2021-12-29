#ifndef __DATABASE_BLOCK__
#define __DATABASE_BLOCK__

#include "../port/port.h"

namespace database {

// Defines the block file format for the db
// These classes are not thread safe

#define BLOCK_SIZE 4096

class BlockReader {
public:
    explicit BlockReader(File *file, off_t offset): _file(file), _offset(offset) { }
    ~BlockReader() = default;

    // TODO: change to std::byte
    ssize_t Read(char *buf, size_t len);

    [[nodiscard]] File* GetFile() const { return this->_file; };
    [[nodiscard]] off_t GetOriginalOffset() const { return this->_offset; };

private:
    File *_file;
    off_t _offset;
};

class BlockWriter {
public:
    explicit BlockWriter(File *file, off_t offset): _file(file), _offset(offset) {}
    ~BlockWriter() = default;

    size_t Write(char *data, size_t len);

    [[nodiscard]] File* GetFile() const { return this->_file; };
    [[nodiscard]] off_t GetOriginalOffset() const { return this->_offset; };

private:
    File *_file;
    off_t _offset;
};

} // end namespace

#endif // end __DATABASE_BLOCK__