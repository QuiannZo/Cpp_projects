#include <stdbool.h>

typedef struct cell_t {
    char status;
    bool checked;
}cell_t;

cell_t** create_matrix(int rows, int cols);
void delete_matrix(cell_t** matrix, int rows);
void print_matrix(cell_t** matrix, int rows, int cols);