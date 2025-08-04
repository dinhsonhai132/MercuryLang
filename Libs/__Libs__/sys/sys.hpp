#ifndef LIB_SYS_H
#define LIB_SYS_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <windot11.h>

#ifdef str
#undef str
#endif

inline int sys_cmd(const std::string &cmd) {
    return system(cmd.c_str());
}

inline std::string sys_get_content(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return "";
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

inline int write_file_content(const std::string &path, const std::string &content) {
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    if (!file.is_open()) return -1;
    file.write(content.data(), content.size());
    return 0;
}

inline std::string read_file_content(const std::string &path, int size) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return "";
    std::string buffer(size, '\0');
    file.read(&buffer[0], size);
    buffer.resize(file.gcount());
    return buffer;
}

inline std::vector<uint8_t> string_to_uint8_t(const std::string &str) {
    std::vector<uint8_t> uint8tstr(str.size());
    std::copy(str.begin(), str.end(), uint8tstr.begin());
    return uint8tstr;
}

inline bool file_exists(const std::string &path) {
    return std::filesystem::exists(path);
}

inline bool is_file(const std::string &path) {
    return std::filesystem::is_regular_file(path);
}

inline bool is_dir(const std::string &path) {
    return std::filesystem::is_directory(path);
}

inline bool move_dir(const std::string &old_path, const std::string &new_path) {
    std::error_code ec;
    std::filesystem::rename(old_path, new_path, ec);
    return !ec;
}

inline size_t file_size(const std::string &path) {
    if (!std::filesystem::exists(path)) return 0;
    return std::filesystem::file_size(path);
}

inline bool remove_file(const std::string &path) {
    return std::filesystem::remove(path);
}

inline bool create_file(const std::string &path) {
    std::ofstream file(path);
    return file.is_open();
}

inline bool move_file(const std::string &old_path, const std::string &new_path) {
    std::error_code ec;
    std::filesystem::rename(old_path, new_path, ec);
    return !ec;
}

inline bool create_dir(const std::string &path) {
    return std::filesystem::create_directory(path);
}

inline bool remove_dir(const std::string &path) {
    return std::filesystem::remove_all(path) > 0;
}

inline std::vector<std::string> list_dir(const std::string &path) {
    std::vector<std::string> files;
    for (auto &p : std::filesystem::directory_iterator(path))
        files.push_back(p.path().string());
    return files;
}

inline bool rename_file(const std::string &old_path, const std::string &new_path) {
    std::error_code ec;
    std::filesystem::rename(old_path, new_path, ec);
    return !ec;
}

inline bool rename_dir(const std::string &old_path, const std::string &new_path) {
    std::error_code ec;
    std::filesystem::rename(old_path, new_path, ec);
    return !ec;
}

inline bool copy_file(const std::string &src, const std::string &dst, bool overwrite = false) {
    std::error_code ec;
    std::filesystem::copy_file(src, dst, overwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none, ec);
    return !ec;
}

inline bool copy_dir(const std::string &src, const std::string &dst, bool overwrite = false) {
    std::error_code ec;
    std::filesystem::copy(src, dst, overwrite ? std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::none, ec);
    return !ec;
}

inline std::string current_path() {
    return std::filesystem::current_path().string();
}

inline bool set_current_path(const std::string &path) {
    std::error_code ec;
    std::filesystem::current_path(path, ec);
    return !ec;
}

#endif // LIB_SYS_H