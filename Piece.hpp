#pragma once

#define VERBOSE true

const int MAX_BOARDSIZE = 10;

class Piece {
protected:
    int x; // row position on board
    int y; // col position on board
    bool isWhite; // to know if piece is black or white
public:
    Piece(int x, int y, bool isWhite); // Piece constructor
    virtual ~Piece() {} // Virtual Piece destructor
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    // Checks if piece is black or white
    bool pieceIsWhite();
    // Moves piece to another specified spot
    virtual void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) = 0;
    // Moves the actual piece to the new coordinates
    void movePiece(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    // Checks if given new position is valid
    bool isValidPos(int x, int y, int boardSizeOnX, int boardSizeOnY);
    // Checks if a piece can be captured on given coordinates
    bool isCapturable(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], bool isWhite);
    // Gets the character from a specified piece, depending if its black or white
    virtual char getPieceType() = 0;
    // Displays the piece type on the terminal (Using getPieceType)
    void displayPiece();
};

class King : public Piece {
public:
    King(int x, int y, bool isWhite);
    void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) override;
    void moveOrCapture(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    char getPieceType() override;
};

class Queen : public Piece {
public:
    Queen(int x, int y, bool isWhite);
    void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) override;
    void moveOrCapture(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    char getPieceType() override;
};

class Rook : public Piece {
public:
    Rook(int x, int y, bool isWhite);
    void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) override;
    void moveOrCapture(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    char getPieceType() override;
};

class Knight : public Piece {
public:
    Knight(int x, int y, bool isWhite);
    void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) override;
    void moveOrCapture(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    char getPieceType() override;
};

class Bishop : public Piece {
public:
    Bishop(int x, int y,bool isWhite);
    void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) override;
    void moveOrCapture(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    char getPieceType() override;
};

class Pawn : public Piece {
public:
    Pawn(int x, int y, bool isWhite);
    void move(Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int x, int y) override;
    void moveOrCapture(int newX, int newY, Piece* board[MAX_BOARDSIZE][MAX_BOARDSIZE], int boardSizeOnX, int boardSizeOnY);
    char getPieceType() override;
};