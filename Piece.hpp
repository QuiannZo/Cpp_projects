#pragma once

#define VERBOSE true

class Piece {
protected:
    int x; // row position on board
    int y; // col position on board
    bool moved; // to know if piece has moved
public:
    Piece(int x, int y); // Piece constructor
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    virtual void move(int newX, int newY) = 0;
};

class King : public Piece {
public:
    King(int x, int y);
    void move(int newX, int newY) override;
};

class Queen : public Piece {
public:
    Queen(int x, int y);
    void move(int newX, int newY) override;
};

class Rook : public Piece {
public:
    Rook(int x, int y);
    void move(int newX, int newY) override;
};

class Knight : public Piece {
public:
    Knight(int x, int y);
    void move(int newX, int newY) override;
};

class Bishop : public Piece {
public:
    Bishop(int x, int y);
    void move(int newX, int newY) override;
};

class Pawn : public Piece {
public:
    Pawn(int x, int y);
    void move(int newX, int newY) override;
};