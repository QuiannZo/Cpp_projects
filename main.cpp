#include <iostream>
#include <string>

#include "Piece.hpp"

int main(int argc, char* argv[]) {
    bool verbose = false;
    if (argc > 1 && std::string(argv[1]) == "-v") {
        verbose = true;
    }
    return EXIT_SUCCESS;

    // Get board size
    int boardSizeOnX, boardSizeOnY;
    std::cin >> boardSizeOnX >> boardSizeOnY;

    // Get amount of rounds
    int rounds;
    std::cin >> rounds;

    // Create 2D array of Piece objects to represent a board
    Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE];

    // Cycle through board array to find and set pieces on the board
    for (int i = 0; i < boardSizeOnX; i++) {
        for (int j = 0; j < boardSizeOnY; j++) {
            // Get piece type found on board
            char pieceType;
            std::cin >> pieceType;
            // If '-' assign to null
            if (pieceType == '-') {
                board[i][j] = nullptr;
            } else { // Else assign isWhite to true if its uppercase, if lowercase assing to false
                bool isWhite = isupper(pieceType);
                pieceType = tolower(pieceType); // Switch pieceType to lowercase (to use switch)

                switch (pieceType)
                {
                    case 'r':
                        board[i][j] = new King(i, j, isWhite);
                        break;
                    case 'q':
                        board[i][j] = new Queen(i, j, isWhite);
                        break;
                    case 't':
                        board[i][j] = new Rook(i, j, isWhite);
                        break;
                    case 'c':
                        board[i][j] = new Knight(i, j, isWhite);
                        break;
                    case 'a':
                        board[i][j] = new Bishop(i, j, isWhite);
                        break;
                    case 'p':
                        board[i][j] = new Pawn(i, j, isWhite);
                        break;

                }
            }
        }
    }

    // Cycle for rounds
    for (int round = 0; round < rounds; round++) {
        // White pieces turn
        for (int i = 0; i < boardSizeOnX; i++) {
            for (int j = 0; j < boardSizeOnY; j++) {
                Piece* piece = board[i][j];
                if (piece->isWhite && piece != nullptr) {
                    piece->move(board, boardSizeOnX, boardSizeOnY);
                }
            }
        }

        // Black pieces turn
        for (int i = 0; i < boardSizeOnX; i++) {
            for (int j = 0; j < boardSizeOnY; j++) {
                Piece* piece = board[i][j];
                if (!piece->isWhite && piece != nullptr) {
                    piece->move(board, boardSizeOnX, boardSizeOnY);
                }
            }
        }
    }
}