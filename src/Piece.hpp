#pragma once

#define VERBOSE true

const int MAX_BOARDSIZE = 10;

class Piece {
protected:
    int x; // row position on board
    int y; // col position on board
    bool isWhite; // to know if piece is black or white
    int speed;
public:
    Piece(int x, int y, bool isWhite); // Piece constructor
    virtual ~Piece() {} // Virtual Piece destructor
    // Checks if piece is black or white
    bool pieceIsWhite();
    // Moves piece to another specified spot
    virtual void move(Piece*** board, int boardSizeOnX, int boardSizeOnY) = 0;
    // Moves the piece to the specified spot
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY);
    // Moves the piece or captures depending on rand, if even possible.
    virtual void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) = 0;
    // Moves the piece and leaves a copy in the original position.
    virtual void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) = 0;
    // Checks if given new position is valid
    bool isValidPos(int x, int y, int boardSizeOnX, int boardSizeOnY);
    // Checks if a piece can be captured on given coordinates
    bool isCapturable(int newX, int newY, Piece*** board, bool isWhite);
    // Gets the character from a specified piece, depending if its black or white
    virtual char getPieceType() = 0;
    // Gets piece speed
    virtual int getPieceSpeed() = 0;
    // Displays the piece type on the terminal (Using getPieceType)
    void displayPiece();
};

class King : public Piece {
public:
    King(int x, int y, bool isWhite);
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) override;
    void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

class Queen : public Piece {
public:
    Queen(int x, int y, bool isWhite);
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) override;
    void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

class Rook : public Piece {
public:
    Rook(int x, int y, bool isWhite);
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) override;
    void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

class Knight : public Piece {
public:
    Knight(int x, int y, bool isWhite);
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) override;
    void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

class Bishop : public Piece {
public:
    Bishop(int x, int y,bool isWhite);
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) override;
    void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

class Pawn : public Piece {
public:
    Pawn(int x, int y, bool isWhite);
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rand) override;
    void moveAndDuplicate(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

Piece*** createMatrix(int rows, int cols);

void deleteMatrix(Piece*** matrix, int rows, int cols);

void printMatrix(Piece*** matrix, int rows, int cols);

void readMatrix(std::istream& arg, Piece*** board, int rows, int cols);

void readMatrix(std::ifstream& arg, Piece*** board, int rows, int cols);

void run(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rounds, bool verbose);