#include "pgof/pgofApp.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

namespace {

void printUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <total-spaces>\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    try {
        const int totalSpaces = std::stoi(argv[1]);
        pgof::PgofApp app{totalSpaces};

        std::cout << app.getReportText() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Failed to initialize PGOF: " << error.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
