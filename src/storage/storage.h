#ifndef __STORAGE__
#define __STORAGE__

#include <string>
#include <optional>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <filesystem>
#include <iostream>
#include <condition_variable>
#include <atomic>

uintmax_t file_len(const std::string &path_str);

class InternalStorage final {
    public:
        InternalStorage(const std::filesystem::path &path);
        InternalStorage(const std::string &path);
        ~InternalStorage();

        uint64_t append(const std::string &content);
        std::string_view read();
        std::string_view read_from(uint64_t start);
        std::string_view read_from(uint64_t start, std::optional<uint64_t> end);
    
    private:
        void start() noexcept;
        void flush();

        mutable std::string _path;
        mutable std::thread _flush_thread;
        mutable std::mutex _flush_mutex;
        bool _flush_now;

        std::vector<unsigned char> mem_table;
};

#endif