#include <iostream>
#include <string>
#include <fstream>
#include <string>

#include "Piece.hpp"

int main(int argc, char* argv[]) {
    int boardSizeOnX = 0, boardSizeOnY = 0;
    int rounds = 0;
    Piece*** board;
    bool verbose = false;

    Controller controller;

    if (argc > 1 && std::string(argv[1]) == "-v") {
        verbose = true;
    }

    if (argc > 2 && std::string(argv[2]) == "-f" || argc > 2 && std::string(argv[1]) == "-f" || argc > 1 && verbose == false) {
        std::string filename;

        if(verbose == true && argc > 3){
            filename = std::string(argv[3]);
        } else if (verbose == false && argc > 2) {
            filename = std::string(argv[2]);
        } else if (verbose == false && argc > 1 && argv[1] == "-f"){
            std::cout << "Ingrese el nombre del archivo: ";
            std::cin >> filename;
        } else {
            std::cout << "Ingrese el nombre del archivo: ";
            std::cin >> filename;
        }

        std::ifstream file(filename);
        if (!file) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            return 1;
        }

        // Read initial values.
        std::string line;

        // Get board size
        file >> boardSizeOnX >> boardSizeOnY;
        std::getline(file, line);

        // Get amount of rounds
        file >> rounds;
        std::getline(file, line);

        // Create matrix of Piece objects to represent a board
        board = controller.createMatrix(boardSizeOnX, boardSizeOnY);

        // Read matrix.
        controller.readMatrix(file, board, boardSizeOnX, boardSizeOnY);

        // Close the file
        file.close();
    } else {
        // Read std input.
        // Get board size
        std::cin >> boardSizeOnX >> boardSizeOnY;

        // Get amount of rounds
        std::cin >> rounds;

        // Create matrix of Piece objects to represent a board
        board = controller.createMatrix(boardSizeOnX, boardSizeOnY);

        // Cycle through board array to find and set pieces on the board
        controller.readMatrix(std::cin, board, boardSizeOnX, boardSizeOnY);
    }

    // Run the simulation.
    controller.run(board, boardSizeOnX, boardSizeOnY, rounds, verbose);

    // Display the final board.
    if (!verbose)
        controller.printMatrix(board, boardSizeOnX, boardSizeOnY);
    // Free memory
    controller.deleteMatrix(board, boardSizeOnX, boardSizeOnY);
    return EXIT_SUCCESS;
}