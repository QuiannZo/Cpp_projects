#include <iostream>

#include "Piece.hpp"

Piece::Piece(int x, int y, bool isWhite) : x{x}, y{y}, isWhite{isWhite} {}

bool Piece::isValidPos(int x, int y, int boardSizeOnX, int boardSizeOnY) {
    if (x < boardSizeOnX && x >= 0 && y < boardSizeOnY && y >= 0) {
        return true;
    }
    return false;
}

bool Piece::isCapturable(int newX, int newY, Piece*** board, bool isWhite) {
    Piece* selectedPiece = board[newX][newY];
    // Checks if they are different color and if it isn't nullptr
    if (selectedPiece->pieceIsWhite() != this->isWhite && selectedPiece != nullptr) {
        return true;
    } 
    return false;
}

void Piece::displayPiece() {
    std::cout << getPieceType();
}

inline bool Piece::pieceIsWhite(){
    return isWhite;
}

void Piece::movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    if (isValidPos(newX, newY, boardSizeOnX, boardSizeOnY)) {
        board[newX][newY] = board[x][y];
        board[x][y] = nullptr;
        x = newX;
        y = newY;
    }
}

// // KING

King::King(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void King::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    int possibleMoves[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

    // TODO: Implement percentages logic
}

char King::getPieceType() {
    return isWhite ? 'K' : 'k';
}

int King::getPieceSpeed() {
    return 4;
}

// // QUEEN

Queen::Queen(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Queen::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Queen::getPieceType() {
    return isWhite ? 'Q' : 'q';
}

int Queen::getPieceSpeed() {
    return 5;
}

// // ROOK

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Rook::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Rook::getPieceType() {
    return isWhite ? 'T' : 't';
}

int Rook::getPieceSpeed() {
    return 2;
}

// // KNIGHT

Knight::Knight(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Knight::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Knight::getPieceType() {
    return isWhite ? 'C' : 'c';
}

int Knight::getPieceSpeed() {
    return 6;
}

// // BISHOP

Bishop::Bishop(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Bishop::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Bishop::getPieceType() {
    return isWhite ? 'A' : 'a';
}

int Bishop::getPieceSpeed() {
    return 3;
}

// // PAWN

Pawn::Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Pawn::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Pawn::getPieceType() {
    return isWhite ? 'P' : 'p';
}

int Pawn::getPieceSpeed() {
    return 1;
}

//Crear una matrix e inicializarla con null pointers.
Piece*** createMatrix(int rows, int cols){
    Piece*** matrix = new Piece**[rows];
    for(int i = 0; i < cols; ++i){
        matrix[i] = new Piece*[cols];
    }
    return matrix; // Returns the triple pointer.
}

//Borra la matriz. Primero convierte los campos a nullptr, luego borra las filas, y luego el arreglo apuntando a las filas.
void deleteMatrix(Piece*** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            delete matrix[i][j];
        }
        delete matrix[i];
    }
    delete matrix;
}

void printMatrix(Piece*** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            //Piece* piece = matrix[i][j];
            if(matrix[i][j] == nullptr){
                std::cout << '-';
            } else {
                std::cout << matrix[i][j]->getPieceType();
            }
        }
        std::cout << std::endl;
    }
}

void readMatrix(std::istream& arg, Piece*** board, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Get piece type found on board
            char pieceType;
            arg >> pieceType;
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
}

void readMatrix(std::ifstream& arg, Piece*** board, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Get piece type found on board
            char pieceType;
            arg >> pieceType;
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
}

void run(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rounds, bool verbose){
    // Each of the rounds
    for (int round = 0; round < rounds; round++) {
        // White pieces turn
        // Pieces move by speed (1 - 6). One being the fastest.
        for(int speed = 1; speed <= 6; ++speed){
            for (int i = 0; i < boardSizeOnX; i++) {
                for (int j = 0; j < boardSizeOnY; j++) {
                    Piece* piece = board[i][j];
                    if (piece->pieceIsWhite() && piece != nullptr) {
                        piece->move(board, boardSizeOnX, boardSizeOnY);
                    }
                }
            }
        }

        // Black pieces turn
        // Pieces move by speed (1 - 6). One being the fastest.
        for(int speed = 1; speed <= 6; ++speed){
            for (int i = 0; i < boardSizeOnX; i++) {
                for (int j = 0; j < boardSizeOnY; j++) {
                    Piece* piece = board[i][j];
                    if (!piece->pieceIsWhite() && piece != nullptr && piece->getPieceSpeed() == speed) {
                        piece->move(board, boardSizeOnX, boardSizeOnY);
                    }
                }
            }
        }

        // rounds - 1 because the final round is always shown in main.
        if(verbose == true && round < rounds - 1){
            printMatrix(board, boardSizeOnX, boardSizeOnY);
        }
    }
}