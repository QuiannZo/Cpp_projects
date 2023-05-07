typedef struct Cell {
    char status;
    bool checked;
}Cell;

Cell** create_matrix(int rows, int cols);