#include <stdlib.h>
#include <stdio.h>

#include "refuges.h"

Cell** create_matrix(int rows, int cols){
    Cell** matrix = malloc(rows * sizeof(Cell*));
    for(int i = 0; i < rows; i++){
        matrix[i] = malloc(cols * sizeof(Cell));
    }
    return matrix;
}

void delete_matrix(Cell** matrix, int rows){
    for(int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(Cell** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            putchar(matrix[i][j].status);
        }
        putchar('\n');
    }
}