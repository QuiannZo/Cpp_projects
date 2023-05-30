#include <iostream>

#include "Piece.hpp"

Piece::Piece(int x, int y, bool isWhite) : x{x}, y{y}, isWhite{isWhite} {}

inline int Piece::getX() {
    return x;
}

inline int Piece::getY() {
    return y;
}

inline void Piece::setX(int x) {
    this->x = x;
}

inline void Piece::setY(int y) {
    this->y = y;
}

// King

King::King(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void King::move(int newX, int newY) {
    if ((newX - x) <= 1 && (newY - y) <= 1) {
        setX(newX);
        setY(newY);
    }
}

// Queen

Queen::Queen(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Queen::move(int newX, int newY) {
    // TODO: Implement
}

// Rook

Rook::Rook(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Rook::move(int newX, int newY) {
    // TODO: Implement
}

// Knight

Knight::Knight(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Knight::move(int newX, int newY) {
    // TODO: Implement
}

// Bishop

Bishop::Bishop(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Bishop::move(int newX, int newY) {
    if ((newX - x) == (newY - y)) {
        x = newX;
        y = newY;
    }
}

// Pawn

Pawn::Pawn(int x, int y, bool isWhite) : Piece(x, y, isWhite) {}

void Pawn::move(int newX, int newY) {
    // TODO: Implement
}