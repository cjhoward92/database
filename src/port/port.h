//
// Created by carson on 12/27/21.
//

#ifndef DATABASE_PORT_H
#define DATABASE_PORT_H

#include <string>
#include <stdexcept>
#include <utility>

namespace database {

class File {
public:
    File(std::string  filename): _fd(0), _isOpen(false), _filename(std::move(filename)) {
        if (this->_filename.length() < 2) {
            throw std::invalid_argument("filename must be a valid file");
        }
    };
    ~File() {
        this->Close();
    };

    void Open();
    void Close();
    ssize_t Read(char *buf, size_t length);
    ssize_t Read(char *buf, size_t length, off_t position);
    ssize_t Write(const char *buf, size_t length);
    ssize_t Write(const char *buf, size_t length, off_t position);

    [[nodiscard]] int GetFileDescriptor() const;
    [[nodiscard]] std::string GetFilename() const;

private:
    int _fd;
    std::string _filename;
    bool _isOpen;
};
} // end namespace

#endif //DATABASE_PORT_H
