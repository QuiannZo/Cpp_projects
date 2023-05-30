#include <iostream>
#include <string>

#include "Piece.hpp"

int main(int argc, char* argv[]) {
    bool verbose = false;
    if (argc > 1 && std::string(argv[1]) == "-v") {
        verbose = true;
    }
    return EXIT_SUCCESS;
}