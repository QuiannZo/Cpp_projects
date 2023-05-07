#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "refuges.h"

int main(void) {
    int rows = 0, cols = 0;
    if(!(scanf("%d %d\n", &rows, &cols) == 2)){
        fprintf(stderr, "Could not read data.");
    }
    cell_t** matrix = (cell_t**)create_matrix(rows, cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            scanf("%c", &matrix[i][j].status);
        }
        getc(stdin);
    }
    print_matrix(matrix, rows, cols);
    delete_matrix(matrix, rows);
}