#include "./Source/mpi.hpp"

#define CUSTOM_VERSION "1.0.0"

void print_help() {
    std::cout << "Usage: " << "mpi <command> [arguments]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  --install <RepoUrl> - Install a library from a GitHub repository." << std::endl;
    std::cout << "  --help - Show this help message." << std::endl;
    std::cout << "  --version - Show version information." << std::endl;
}

int main(int argc, char* argv[]) {    
    if (argc < 2) {
        print_help();
        return 1;
    }

    std::string command = argv[1];
    if (command == "--install") {
        std::string RepoUrl = argv[2];
        return install_lib(RepoUrl);
    } else if (command == "--help") {
        print_help();
        return 0;
    } else if (command == "--version") {
        std::cerr << "Version: " << CUSTOM_VERSION << std::endl;
        return 0;
    }
    
    return 0;
}