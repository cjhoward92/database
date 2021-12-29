//
// Created by carson on 12/28/21.
//

#include "port.h"

#include <fcntl.h>
#include <unistd.h>

using namespace database;

void File::Open() {
    if (this->_isOpen) {
        return;
    }

    this->_fd = open(this->_filename.c_str(), O_RDWR);
    if (this->_fd <= 0) {
        throw std::runtime_error("Unable to open file '" + this->_filename + "'.");
    }

    this->_isOpen = true;
}

void File::Close() {
    if (!this->_isOpen) {
        return;
    }

    int out = close(this->_fd);
    if (out < 0) {
        throw std::runtime_error("Could not close file '" + this->_filename + "'.");
    }

    this->_fd = 0;
    this->_isOpen = false;
}

ssize_t  File::Read(char *buf, size_t length) {
    return this->Read(buf, length, 0);
}

ssize_t File::Read(char *buf, size_t length, off_t position) {
    if (buf == nullptr) {
        throw std::invalid_argument("A data buffer is required");
    }
    if (length < 1) {
        throw std::invalid_argument("length must be greater than 0.");
    }
    if (position < 0) {
        throw std::invalid_argument("position must be 0 or greater.");
    }

    if (!this->_isOpen) {
        this->Open();
    }

    if (lseek(this->_fd, position, SEEK_SET) < 0) {
        throw std::runtime_error("Could not seek file position");
    }

    auto output = read(this->_fd, buf, length);
    if (output < 0) {
        throw std::runtime_error("Could not read file.");
    }

    return output;
}

ssize_t File::Write(const char *buf, size_t length) {
    return this->Write(buf, length, 0);
}

ssize_t File::Write(const char *buf, size_t length, off_t position) {
    if (buf == nullptr) {
        throw std::invalid_argument("A data buffer is required");
    }
    if (length < 1) {
        throw std::invalid_argument("length must be greater than 0.");
    }
    if (position < 0) {
        throw std::invalid_argument("position must be 0 or greater.");
    }

    if (!this->_isOpen) {
        this->Open();
    }

    if (lseek(this->_fd, position, SEEK_SET) < 0) {
        throw std::runtime_error("Could not seek file position");
    }

    auto output = write(this->_fd, buf, length);
    if (output < 0) {
        throw std::runtime_error("Could not write to file.");
    }

    return output;
}

int File::GetFileDescriptor() const {
    return this->_fd;
}

// TODO: Prevent a copy?
std::string File::GetFilename() const {
    return this->_filename;
}
