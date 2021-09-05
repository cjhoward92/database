#include "storage.h"

uintmax_t file_len(const std::string &path_str) {
    return std::filesystem::file_size(path_str);
}

static std::condition_variable do_flush;

void InternalStorage::flush() {
    while (true) {
        std::unique_lock<std::mutex> lock(this->_flush_mutex);
        do_flush.wait(lock, [&]{ return this->_flush_now; });

        auto mem_table = this->mem_table;
        std::cout << "flushing" << std::endl;
        std::cout << "vec len: " << mem_table.size() << std::endl;

        this->_flush_now = false;
        lock.unlock();
        do_flush.notify_all();
    }
}

void InternalStorage::start() noexcept {
    this->_flush_now = false;
    this->_flush_thread = std::thread{&InternalStorage::flush, this};
}

InternalStorage::InternalStorage(const std::filesystem::path &path) {
    this->_path = path.string();
    this->start();
}

InternalStorage::InternalStorage(const std::string &path) {
    this->_path = path;
    this->start();
}

InternalStorage::~InternalStorage() {
    this->_flush_thread.join();
}

uint64_t InternalStorage::append(const std::string &content) {
    if (content.size() == 0) {
        return 0;
    }

    uint64_t total = 1 + content.size();
    this->mem_table.push_back('\n');
    for (char const &c: content) {
        this->mem_table.push_back(c);
    }

    if (this->mem_table.size() > 10) {
        std::scoped_lock s(this->_flush_mutex);
        this->_flush_now = true;
    }
    do_flush.notify_one();

    return total;
}

