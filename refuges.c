#include <stdlib.h>
#include <stdio.h>

#include "refuges.h"

cell_t** create_matrix(int rows, int cols){
    
}

// Uses "depth-first search" recursive algorithm to visit and mark corresponding cells of a zone as checked if not already
// This is so that when find_max_size runs, it doesn't call this function on already checked zones.
// Keeps track of the size of the zone and returns it
int zone_checker(cell_t** matrix, int row, int col, int rows, int cols, char status) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return 0;
    }
    if (matrix[row][col].status != '-') {
        return 0;
    }
    int zone_size = 1;
    matrix[row][col].status = status;
    zone_size += zone_checker(matrix, row + 1, col, rows, cols, status);
    zone_size += zone_checker(matrix, row - 1, col, rows, cols, status);
    zone_size += zone_checker(matrix, row, col + 1, rows, cols, status);
    zone_size += zone_checker(matrix, row, col - 1, rows, cols, status);
    return zone_size;
}

// Loops through the area to find '-' that isn't checked, if found then uses zone_checker
// Uses zone_checker's return value to compare to the biggest size found
// Returns the biggest zone size found
int find_max_size(cell_t** matrix, int rows, int cols, char status, int* safe_zone_count) {
    int biggest_size = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (matrix[row][col].status == '-') {
                int size = zone_checker(matrix, row, col, rows, cols, status);
                if (size > biggest_size) {
                    biggest_size = size;
                }
            }
        }
    }
    return biggest_size;
}  

// Sets every checked bool in the cells in area to false
// This is to be able to use zone_checker again on change_status()
void reset_checked(cell_t** matrix, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; cols++) {
            matrix[row][col].checked = false;
        }
    }
}

// Changes the status of a specific cell
void change_status(cell_t** matrix, int rows, int cols, int biggest_size, char status, char new_status) {
    // reset_checked(rows, cols);
    // loop through rows and cols of area
    //     if area[row][col].status = status
    //         int size = zone_checker(row, col);
    //         if (size == biggest_size)
    //             area[row][col].status = new_status;
    reset_checked(matrix, rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (matrix[row][col].status == status) {
                int size = zone_checker(matrix, row, col, rows, cols, status);
                if (size == biggest_size) {
                    matrix[row][col].status = new_status;
                }
            }
        }
    }
}