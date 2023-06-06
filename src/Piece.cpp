#include <iostream>
#include <random>
#include <string>
#include <fstream>

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

void Piece::movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {
    if (isValidPos(newX, newY, boardSizeOnX, boardSizeOnY)) {
        board[newX][newY] = board[x][y];
        if (!duplicate) {
            board[x][y] = nullptr;
        }
        x = newX;
        y = newY;
    }
}

// // KING

King::King(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void King::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 7);
    int index = dis(gen);

    // Pick a random x and y from the possible directions
    int targetX = directions[index][0] + x;
    int targetY = directions[index][1] + y;

    // Checks if its not out of bounds and is a nullptr
    if (isValidPos(targetX, targetY, boardSizeOnX, boardSizeOnY) && board[targetX][targetY] == nullptr) {
        movePiece(targetX, targetY, board, boardSizeOnX, boardSizeOnY, duplicate);
    }
}

void King::moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {
    int directions[8][2] = {
        {-1, -1}, // bottom left
        {-1, 0},  // left
        {-1, 1},  // top left
        {0, -1},  // bottom
        {0, 1},   // top
        {1, -1},  // bottom right
        {1, 0},   // right
        {1, 1}    // top right
    };
    int capturablePieces[8][2];
    int capturableCount = 0;

    // Loop to save all possible capturable pieces on capturablePieces array
    for (int i = 0; i < 8; i++) {
        int captureX = directions[i][0] + x; // x is the current x value for the piece
        int captureY = directions[i][1] + y; // y is the current y value for the piece
        // If piece is not out of bounds, is the opposite color and isn't a nullptr
        if (isValidPos(captureX, captureY, boardSizeOnX, boardSizeOnY) && (board[captureX][captureY]->pieceIsWhite() != this->pieceIsWhite()) && (board[captureX][captureY] != nullptr)) {
            // Set position as capturable on capturablePieces array
            capturablePieces[capturableCount][0] = captureX;
            capturablePieces[capturableCount][1] = captureY;
            capturableCount++;
        }
    }

    if (capturableCount > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> indexdis(0, capturableCount);
        int index = indexdis(gen);

        int captureX = capturablePieces[index][0];
        int captureY = capturablePieces[index][1];

        std::uniform_int_distribution<> chancedis(0, 100);
        int chance = chancedis(gen);
        
        // 50% chance to capture the piece
        if (chance < 50) {
            delete board[captureX][captureY];
            movePiece(captureX, captureY, board, boardSizeOnX, boardSizeOnY, duplicate);
            return;
        }
    }
    // 50% chance to move randomly or if no pieces were capturable
    randomMove(board, boardSizeOnX, boardSizeOnY, duplicate);
}

void King::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    bool duplicate = false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int chance = dis(gen);

    // 10% chance (with duplication)
    if (chance < 10) {
        duplicate = true;
    }
    // 60% chance (normal move or capture with no duplication)
    if (chance < 70) {
        moveOrCapture(board, boardSizeOnX, boardSizeOnY, duplicate);
    }
    // Else (30% chance) it doesn't do anything
}

char King::getPieceType() {
    return isWhite ? 'K' : 'k';
}

int King::getPieceSpeed() {
    return 4;
}

// // QUEEN

Queen::Queen(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Queen::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> indexdis(0, 7);
    int index = indexdis(gen);

    // Pick a random x and y from the possible directions
    int directionX = directions[index][0];
    int directionY = directions[index][1];

    // Calculate the max amount of steps the piece can take
    int maxSteps = std::min(boardSizeOnX - x - 1, boardSizeOnY - y - 1);

    // Generate a random number for the number of possible steps
    std::uniform_int_distribution<> stepsdis(1, maxSteps);
    int steps = stepsdis(gen);

    // Sets targetX and targetY to the direction times steps, if x or y is 0, no change will be made to them
    int targetX = x + (directionX * steps);
    int targetY = y + (directionY * steps);

    if (isValidPos(targetX, targetY, boardSizeOnX, boardSizeOnY) && board[targetX][targetY] == nullptr) {
        movePiece(targetX, targetY, board, boardSizeOnX, boardSizeOnY, duplicate);
    }
}

void Queen::moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {
    int directions[8][2] = {
        {-1, -1}, // bottom left
        {-1, 0},  // left
        {-1, 1},  // top left
        {0, -1},  // bottom
        {0, 1},   // top
        {1, -1},  // bottom right
        {1, 0},   // right
        {1, 1}    // top right
    };
    int capturablePieces[8][2];
    int capturableCount = 0;

    // Loop to save all possible capturable pieces on capturablePieces array
    for (int i = 0; i < 8; i++) {
        int captureX = x; // x is the current x value for the piece
        int captureY = y; // y is the current y value for the piece
        
        // For every direction, check all available spaces
        while (true) {
            captureX += directions[i][0];
            captureY += directions[i][1];

            // If current position is out of bounds, break
            if (!isValidPos(captureX, captureY, boardSizeOnX, boardSizeOnY)) {
                break;
            }

            // If found a piece of opposite color, set as capturable and break
            if ((board[captureX][captureY]->pieceIsWhite() != this->pieceIsWhite()) && (board[captureX][captureY] != nullptr)) {
                capturablePieces[capturableCount][0] = captureX;
                capturablePieces[capturableCount][1] = captureY;
                capturableCount++;
                break;
            }

            // If none of the above happen, but the position isn't empty, it means there's an ally piece in that location, then break
            if (board[captureX][captureY] != nullptr) {
                break;
            }
        }
    }

    if (capturableCount > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> indexdis(0, capturableCount);
        int index = indexdis(gen);

        int captureX = capturablePieces[index][0];
        int captureY = capturablePieces[index][1];

        std::uniform_int_distribution<> chancedis(0, 100);
        int chance = chancedis(gen);
        
        // 50% chance to capture the piece
        if (chance < 50) {
            delete board[captureX][captureY];
            movePiece(captureX, captureY, board, boardSizeOnX, boardSizeOnY, duplicate);
            return;
        }
    }
    // 50% chance to move randomly or if no pieces were capturable
    randomMove(board, boardSizeOnX, boardSizeOnY, duplicate);
}

void Queen::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    bool duplicate = false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    int chance = dis(gen);

    // 10% chance (with duplication)
    if (chance < 10) {
        duplicate = true;
    }
    // 60% chance (normal move or capture with no duplication)
    if (chance < 70) {
        moveOrCapture(board, boardSizeOnX, boardSizeOnY, duplicate);
    }
    // Else (30% chance) it doesn't do anything
}

char Queen::getPieceType() {
    return isWhite ? 'Q' : 'q';
}

int Queen::getPieceSpeed() {
    return 5;
}

// // ROOK

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Rook::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Rook::moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Rook::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {
    
}

char Rook::getPieceType() {
    return isWhite ? 'T' : 't';
}

int Rook::getPieceSpeed() {
    return 2;
}

// // KNIGHT

Knight::Knight(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Knight::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Knight::moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Knight::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {

}

char Knight::getPieceType() {
    return isWhite ? 'C' : 'c';
}

int Knight::getPieceSpeed() {
    return 6;
}

// // BISHOP

Bishop::Bishop(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Bishop::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Bishop::moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Bishop::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {

}

char Bishop::getPieceType() {
    return isWhite ? 'A' : 'a';
}

int Bishop::getPieceSpeed() {
    return 3;
}

// // PAWN

Pawn::Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Pawn::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Pawn::moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {

}

void Pawn::move(Piece*** board, int boardSizeOnX, int boardSizeOnY) {

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