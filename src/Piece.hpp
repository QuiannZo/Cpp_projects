/**
*@file Piece.hpp
*@brief Header files for the chess pieces logic.
*
*This code contains the logic of the father Piece class and its derivate classes.
*/
#pragma once

#define VERBOSE true

/**
 * @brief The Piece base class.
 *
 *The class contains the basic methos required to create the chess pieces. All pieces inherit from this class.
 */
class Piece {
protected:
    int x; // row position on board
    int y; // col position on board
    bool isWhite; // to know if piece is black or white
    bool hasMoved; // to know if piece has moved on the round
    int speed;
    bool firstMove;
public:
  /**
   * @brief Constructor of piece.
   *
   * @param x The x coordinate of the piece position
   * @param y The y coordinate of the piece  position
   * @param isWhite Color of the piece
   */
    Piece(int x, int y, bool isWhite); // Piece constructor
  /**
   * @brief Checks if piece is black or white
   */
    bool pieceIsWhite();
  /**
   * @brief Sets hasMoved to true or false
   *
   * @param moved Boolean for setting movement
   */
    inline void setMoved(bool moved);
  /**
   * @brief returns hasMoved state
   *
   * @param moved Boolean for checking movement
   */
    inline bool pieceHasMoved();
  /**
   * @brief Moves piece to another specified spot
   *
   * @param board the matrix board
   * @param boardSizeOnX board size on X
   * @param boardSizeOnY board size on y
   */
    virtual void move(Piece*** board, int boardSizeOnX, int boardSizeOnY) = 0;
  /**
   * @brief Moves the piece to the specified spot
   *
   * @param newX new x position
   * @param newY new y position
   * @param board the matrix board
   * @param boardSizeOnX board size on X
   * @param boardSizeOnY board size on y
   * @param duplicate boolean to indicate if the piece should be duplicated
   */
    virtual void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) = 0;
  /**
   * @brief Moves the piece randomly on its available positions
   *
   * @param board the matrix board
   * @param boardSizeOnX board size on X
   * @param boardSizeOnY board size on y
   * @param duplicate boolean to indicate if the piece should be duplicated
   */
    virtual void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) = 0;
  /**
   * @brief Moves the piece or captures depending on rand, if even possible.
   *
   * @param board the matrix board
   * @param boardSizeOnX board size on X
   * @param boardSizeOnY board size on y
   * @param duplicate boolean to indicate if the piece should be duplicated
   */
    virtual void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) = 0;
    // 
  /**
   * @brief Checks if given new position is valid
   *
   * @param x x position to check
   * @param y y position to check
   * @param boardSizeOnX board size on X
   * @param boardSizeOnY board size on y
   */
    bool isValidPos(int x, int y, int boardSizeOnX, int boardSizeOnY);
  /**
   * @brief Checks if a piece can be captured on given coordinates
   *
   * @param newX new x position
   * @param newY new y position
   * @param board the matrix board
   * @param isWhite boolean to check team
   * @param maxX maximum possible x value
   * @param maxY maximum possible y value
   */
    bool isCapturable(int newX, int newY, Piece*** board, bool isWhite, int maxX, int maxY);
  /**
   * @brief Gets the character from a specified piece, depending if its black or white
   */
    virtual char getPieceType() = 0;
  /**
   * @brief Gets piece speed
   */
    virtual int getPieceSpeed() = 0;
  /**
   * @brief Displays the piece type on the terminal (Using getPieceType)
   */
    void displayPiece();
  /**
   * @brief returns first move
   */
    inline bool getFirstMove();
  /**
   * @brief Sets first move
   */
    void setFirstMove(bool first);
};

/**
 * @class King
 * @brief King piece. Inherits from piece
 */
class King : public Piece {
public:
    /**
     * @brief Constructor for the King
     * @param x x position on the board
     * @param y y position on the board
     * @param isWhite boolean to set piece color
     */
    King(int x, int y, bool isWhite);
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) override;
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void move(Piece*** board, int boardSizeOnX, int boardSizeOnY) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

/**
 * @class Queen
 * @brief Queen piece. Inherits from piece
 */
class Queen : public Piece {
public:
    /**
     * @brief Constructor for the Queen
     * @param x x position on the board
     * @param y y position on the board
     * @param isWhite boolean to set piece color
     */
    Queen(int x, int y, bool isWhite);
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) override;
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

/**
 * @class Rook
 * @brief Rook piece. Inherits from piece
 */
class Rook : public Piece {
public:
    /**
     * @brief Constructor for the Rook
     * @param x x position on the board
     * @param y y position on the board
     * @param isWhite boolean to set piece color
     */
    Rook(int x, int y, bool isWhite);
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) override;
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

/**
 * @class Knight
 * @brief Knight piece. Inherits from piece
 */
class Knight : public Piece {
public:
    /**
     * @brief Constructor for the knight
     * @param x x position on the board
     * @param y y position on the board
     * @param isWhite boolean to set piece color
     */
    Knight(int x, int y, bool isWhite);
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) override;
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

/**
 * @class Bishop
 * @brief Bishop piece. Inherits from piece
 */
class Bishop : public Piece {
public:
    /**
     * @brief Constructor for the Bishop
     * @param x x position on the board
     * @param y y position on the board
     * @param isWhite boolean to set piece color
     */
    Bishop(int x, int y, bool isWhite);
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) override;
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

/**
 * @class Pawn
 * @brief Pawn piece. Inherits from piece
 */
class Pawn : public Piece {
public:
    /**
     * @brief Constructor for the Pawn
     * @param x x position on the board
     * @param y y position on the board
     * @param isWhite boolean to set piece color
     */
    Pawn(int x, int y, bool isWhite);
    void movePiece(int newX, int newY, Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void randomMove(Piece*** board, int boardSizeOnX, int boardSizeY, bool duplicate) override;
    void moveOrCapture(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) override;
    void move(Piece*** board, int x, int y) override;
    char getPieceType() override;
    int getPieceSpeed() override;
};

/**
 * @class Controller
 * @brief The controller class controlls the game initialization and the matrix and memory management
 */
class Controller {
  public:
      /**
     * @brief default Constructor
     */
    Controller();

    /**
     * @brief Allocates space for the matrix
     * @param rows number of rows
     * @param cols number of cols
     */
    Piece*** createMatrix(int rows, int cols);

    /**
     * @brief Deletes the space allocated for the matrix
     * @param matrix the matrix to be removed
     * @param rows number of rows
     * @param cols number of cols
     */
    void deleteMatrix(Piece*** matrix, int rows, int cols);

    /**
     * @brief Prints the matrix
     * @param matrix the matrix to be printed
     * @param rows number of rows
     * @param cols number of cols
     */
    void printMatrix(Piece*** matrix, int rows, int cols);

    /**
     * @brief Reads input for getting the pieces and storing them in the matrix
     * @param matrix the matrix to be edited
     * @param rows number of rows
     * @param cols number of cols
     */
    void readMatrix(std::istream& arg, Piece*** board, int rows, int cols);

    /**
     * @brief Reads file for getting the pieces and storing them in the matrix
     * @param matrix the matrix to be edited
     * @param rows number of rows
     * @param cols number of cols
     */
    void readMatrix(std::ifstream& arg, Piece*** board, int rows, int cols);

    /**
     * @brief Runs the program and prints the results of the simulation as indicated by the user
     * @param matrix the matrix to be edited and printed
     * @param rows number of rows
     * @param cols number of cols
     */
    void run(Piece*** board, int boardSizeOnX, int boardSizeOnY, int rounds, bool verbose);
};