#include <iostream>

#include "Piece.hpp"

Piece::Piece(int x, int y, bool isWhite) : x{x}, y{y}, isWhite{isWhite} {}

bool Piece::isValidPos(int x, int y, int boardSizeOnX, int boardSizeOnY) {
    if (x < boardSizeOnX && x >= 0 && y < boardSizeOnY && y >= 0) {
        return true;
    }
    return false;
}

bool Piece::isCapturable(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], bool isWhite) {
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

void Piece::movePiece(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    if (isValidPos(newX, newY, boardSizeOnX, boardSizeOnY)) {
        board[newX][newY] = board[x][y];
        board[x][y] = nullptr;
        x = newX;
        y = newY;
    }
}

// // KING

King::King(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void King::move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    int possibleMoves[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

    // TODO: Implement percentages logic
}

char King::getPieceType() {
    return isWhite ? 'K' : 'k';
}

// // QUEEN

Queen::Queen(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Queen::move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Queen::getPieceType() {
    return isWhite ? 'Q' : 'q';
}

// // ROOK

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Rook::move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Rook::getPieceType() {
    return isWhite ? 'T' : 't';
}

// // KNIGHT

Knight::Knight(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Knight::move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Knight::getPieceType() {
    return isWhite ? 'C' : 'c';
}

// // BISHOP

Bishop::Bishop(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Bishop::move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Bishop::getPieceType() {
    return isWhite ? 'A' : 'a';
}

// // PAWN

Pawn::Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Pawn::move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY) {
    // TODO: Implement
}

char Pawn::getPieceType() {
    return isWhite ? 'P' : 'p';
}