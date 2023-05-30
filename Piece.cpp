#include <iostream>

#include "Piece.hpp"

Piece::Piece(int x, int y) {
    this->x = x;
    this->y = y;
    moved = false;
}

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

King::King(int x, int y) : Piece(x, y) {}

void King::move(int newX, int newY) {
    if ((newX - x) <= 1 && (newY - y) <= 1) {
        setX(newX);
        setY(newY);
    }
}

// Queen

Queen::Queen(int x, int y) : Piece(x, y) {}

void Queen::move(int newX, int newY) {
    // TODO: Implement
}

// Rook

Rook::Rook(int x, int y) : Piece(x, y) {}

void Rook::move(int newX, int newY) {
    // TODO: Implement
}

// Knight

Knight::Knight(int x, int y) : Piece(x, y) {}

void Knight::move(int newX, int newY) {
    // TODO: Implement
}

// Bishop

Bishop::Bishop(int x, int y) : Piece(x, y) {}

void Bishop::move(int newX, int newY) {
    if ((newX - x) == (newY - y)) {
        x = newX;
        y = newY;
    }
}

// Pawn

Pawn::Pawn(int x, int y) : Piece(x, y) {}

void Pawn::move(int newX, int newY) {
    // TODO: Implement
}