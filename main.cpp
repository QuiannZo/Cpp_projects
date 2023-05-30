#include <iostream>
#include <string>

#include "Piece.hpp"

int main(int argc, char* argv[]) {
    bool verbose = false;
    if (argc > 1 && std::string(argv[1]) == "-v") {
        verbose = true;
    }

    Piece* king = new King(4, 2);

    king->move(5, 1);
    king->move(6, 2);
    king->move(8, 2);
    std::cout << "end of program" << std::endl;
    return EXIT_SUCCESS;
}