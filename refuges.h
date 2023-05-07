#include <stdbool.h>

typedef struct cell_t {
    char status;
    bool checked;
}cell_t;

cell_t** create_matrix(int rows, int cols);
void delete_matrix(cell_t** matrix, int rows);
void print_matrix(cell_t** matrix, int rows, int cols);
int zone_checker(cell_t** matrix, int row, int col, int rows, int cols, char status);
int find_max_size(cell_t** matrix, int rows, int cols, char status, int* safe_zone_count);
void reset_checked(cell_t** matrix, int rows, int cols);
void change_status(cell_t** matrix, int rows, int cols, int biggest_size, char status, char new_status);