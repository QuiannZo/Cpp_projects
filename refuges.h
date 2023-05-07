#include <stdbool.h>

typedef struct Cell {
    char status;
    bool checked;
}Cell;

Cell** create_matrix(int rows, int cols);
void delete_matrix(Cell** matrix, int rows);
void print_matrix(Cell** matrix, int rows, int cols);