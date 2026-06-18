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
        pgof::PgofApp app{};
        app.capacity = std::stoi(argv[1]);
        app.callGarageCapacityService();

        std::cout << "PGOF initialized\n"
                  << "capacity: " << app.capacity << '\n'
                  << "N1: " << app.N1 << '\n'
                  << "N2: " << app.N2 << '\n'
                  << "N3: " << app.N3 << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Failed to initialize PGOF: " << error.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
