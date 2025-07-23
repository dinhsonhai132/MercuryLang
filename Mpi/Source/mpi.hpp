#ifndef MPI_H
#define MPI_H

#include "cmd.hpp"
#include "json.hpp"
#include <regex>

using json = nlohmann::json;

struct Json_mpi {
    std::string name = "";
    std::string version = "";
    std::string description = "";
    std::string author = "";
};

void from_json(const json& j, Json_mpi& mpi) {
    if (j.contains("name"))        j.at("name").get_to(mpi.name);
    if (j.contains("version"))     j.at("version").get_to(mpi.version);
    if (j.contains("description")) j.at("description").get_to(mpi.description);
    if (j.contains("author"))      j.at("author").get_to(mpi.author);
}

bool check_if_true_repo_link_format(const std::string& link) {
    std::regex github_repo_regex(R"(https:\/\/github\.com\/[^\/\s]+\/[^\/\s]+)");
    
    if (std::regex_match(link, github_repo_regex)) {
        return true;
    } else {
        return false;
    }
}

#define PATH_TO_LIB "C:\\MercuryLang\\Libs\\__Libs__"
#define PATH_TO_TEMP "C:\\MercuryLang\\Libs\\Temp"
#define PATH_TO_LIST_LIB "C:\\MercuryLang\\Libs\\__Libs__\\list.txt"
#define INSTALL_PATH "//archive/refs/heads/main.zip"

Json_mpi take_lib_info(const std::string& path_to_json_file) {
    std::string file_content = GetContents_of(path_to_json_file.c_str());

    json j = json::parse(file_content);

    Json_mpi result;
    from_json(j, result);
    return result;
}

int install_lib(const std::string& RepoUrl) {
    std::string fullUrl = RepoUrl + std::string(INSTALL_PATH);
    std::string repo_name = RepoUrl.substr(RepoUrl.find_last_of("/") + 1) + "-main";
    std::string real_repo_name = RepoUrl.substr(RepoUrl.find_last_of("/") + 1);

    std::cout << "Downloading " << repo_name << "..." << std::endl;

    if (!check_if_true_repo_link_format(RepoUrl)) {
        std::cerr << "Invalid repository link format." << std::endl;
        return 1;
    }

    if (!downloadZip(fullUrl, std::string(PATH_TO_TEMP) + "\\lib.zip")) {
        std::cerr << "Failed to download zip file." << std::endl;
        return 1;
    }

    if (!extractZip(std::string(PATH_TO_TEMP) + "\\lib.zip", PATH_TO_LIB)) {
        std::cerr << "Failed to extract zip file." << std::endl;
        return 1;
    }

    if (!deleteZip(std::string(PATH_TO_TEMP) + "\\lib.zip")) {
        std::cerr << "Failed to delete zip file." << std::endl;
        return 1;
    }

    std::vector<std::string> Folders = Get_all_folders(PATH_TO_LIB);
    for (auto &folder : Folders) {
        if (folder == repo_name) {
            std::string path_to_folder = std::string(PATH_TO_LIB) + "\\" + folder;
            std::string path_to_changed_folder = std::string(PATH_TO_LIB) + "\\" + real_repo_name;
            if (!rename_folder(path_to_folder, path_to_changed_folder)) {
                std::cerr << "Failed to rename folder." << std::endl;
                return 1;
            }
            break;
        }
    }

    std::cout << "Done!" << std::endl;
    return 0;
}

#endif