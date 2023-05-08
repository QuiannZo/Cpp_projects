#include <stdlib.h>
#include <stdio.h>

#include "refuges.h"

cell_t** create_matrix(int rows, int cols){
    cell_t** matrix = malloc(rows * sizeof(cell_t*));
    for(int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(cell_t));
    }
    return matrix;
}

void delete_matrix(cell_t** matrix, int rows) {
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(cell_t** matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            putchar(matrix[i][j].new_status);
        }
        putchar('\n');
    }
}

void cpy_status(cell_t** matrix, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j].new_status = matrix[i][j].status;
        }
    }
}

int zone_checker(cell_t** matrix, int row, int col, int rows, int cols, char status) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0;
    }
    if (matrix[row][col].status != status || matrix[row][col].checked == true) {
        return 0;
    }
    int zone_size = 1;
    matrix[row][col].checked = true;
    zone_size += zone_checker(matrix, row + 1, col, rows, cols, status);
    zone_size += zone_checker(matrix, row - 1, col, rows, cols, status);
    zone_size += zone_checker(matrix, row, col + 1, rows, cols, status);
    zone_size += zone_checker(matrix, row, col - 1, rows, cols, status);
    return zone_size;
}

int find_max_size(cell_t** matrix, int rows, int cols, char status, int* safe_zone_count) {
    int biggest_size = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (matrix[row][col].status == '-') {
                int size = zone_checker(matrix, row, col, rows, cols, status);
                if (size > biggest_size) {
                    biggest_size = size;
                    *safe_zone_count = 1;
                } else if (size == biggest_size) {
                    *safe_zone_count += 1;
                }
            }
        }
    }
    return biggest_size;
}  

void reset_checked(cell_t** matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            matrix[row][col].checked = false;
        }
    }
}

void change_status(cell_t** matrix, int rows, int cols, int biggest_size, char status, char new_status) {
    reset_checked(matrix, rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (matrix[row][col].status == status) {
                int size = zone_checker(matrix, row, col, rows, cols, status);
                if (size == biggest_size) {
                    matrix[row][col].new_status = new_status;
                }
            }
            reset_checked(matrix, rows, cols);
        }
    }
}

void read_matrix(FILE* argument, cell_t** matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int character = getc(argument);
            if (character == EOF) {
                printf("invalid data\n");
                exit(EXIT_FAILURE);
            }
            if (character == '\n') {
                printf("invalid data\n");
                exit(EXIT_FAILURE);
            }
            matrix[row][col].status = character;
        }
        int newline = getc(argument);
        if (newline != '\n' && newline != EOF) {
            printf("invalid data\n");
            exit(EXIT_FAILURE);
        }
    }
}