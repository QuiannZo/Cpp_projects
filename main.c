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
    // Read data.
    FILE* filep;
    filep = fopen("input0.txt", "-r");
    if(filep == NULL){
        // Reads std input.
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                scanf("%c", &matrix[i][j].status);
            }
            getc(stdin);
        }
    } else {
        // Reads file.
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                fscanf(filep,"%c", &matrix[i][j].status);
            }
            getc(stdin);
        }
        fclose(filep);
    }
    cpy_status(matrix, rows, cols);
    int safe_zones = 0;
    int max_size = find_max_size(matrix, rows, cols, '-', &safe_zones);
    if(max_size > 1){
        change_status(matrix, rows, cols, max_size, '-', 'R');
        printf("%d\n\n", safe_zones);
    } else {
        printf("0\n\n");
    }
    print_matrix(matrix, rows, cols);
    delete_matrix(matrix, rows);
}