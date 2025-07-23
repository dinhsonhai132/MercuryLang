#ifndef MERCURY_CMD_HEADER_FILE
#define MERCURY_CMD_HEADER_FILE

#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

bool runCommand(std::string cmd) {
    return (system(cmd.c_str()) == 0);
}

bool MakeFile_to(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    file << content;
    file.close();
    return true;
}

std::string GetContents_of(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::vector<std::string> Get_all_files(const std::string& folder) {
    std::vector<std::string> files;
    WIN32_FIND_DATAA fd;
    HANDLE hFind = ::FindFirstFileA((folder + "\\*").c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                files.push_back(fd.cFileName);
            }
        } while (::FindNextFileA(hFind, &fd));
        ::FindClose(hFind);
    }
    return files;
}

std::vector<std::string> Get_all_folders(const std::string& folder) {
    std::vector<std::string> folders;
    WIN32_FIND_DATAA fd;
    HANDLE hFind = ::FindFirstFileA((folder + "\\*").c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                folders.push_back(fd.cFileName);
            }
        } while (::FindNextFileA(hFind, &fd));
        ::FindClose(hFind);
    }
    return folders;
}

bool rename_folder(const std::string& oldPath, const std::string& newPath) {
    std::string ps = "powershell -Command \"Rename-Item -Path '" + oldPath + "' -NewName '" + newPath + "'\"";
    return runCommand(ps);
}

bool downloadZip(const std::string& url, const std::string& destPath) {
    std::string ps = "powershell -Command \"Invoke-WebRequest -Uri '" + url + "' -OutFile '" + destPath + "'\"";
    return runCommand(ps);
}

bool extractZip(const std::string& zipPath, const std::string& destPath) {
    std::string ps = "powershell -Command \"Expand-Archive -Path '" + zipPath + "' -DestinationPath '" + destPath + "'\"";
    return runCommand(ps);
}

bool deleteZip(const std::string& zipPath) {
    std::string ps = "powershell -Command \"Remove-Item -Path '" + zipPath + "' -Force\"";
    return runCommand(ps);
}

#endif // MERCURY_CMD_HEADER_FILE