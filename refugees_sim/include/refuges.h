/**
*@file refuges.h
*@brief Contains functions for finding safe zones in a matrix of a struct cells.
*The header file contains declarations for the following functions:
*create_matrix() - creates a matrix of cells.
*delete_matrix() - frees the memory of the matrix.
*print_matrix() - prints the status field of each cell in matrix.
*cpy_status() - copies status to new_status in the matrix to later change the biggest groups to 'R'.
*zone_checker() - a funnction that checks the zones in the matrix using recursion.
*find_max_size() - finds the largest safe zone.
*reset_checked() - sets "checked" of each cell in matrix to false.
*change_status() - changes status in the largest safe zone to a new char given.
*/

#ifndef REFUGES_H
#define REFUGES_H

#include <stdbool.h>

typedef struct cell_t {
    char status; /*A char that stores the value of the input matrix.*/
    char new_status; /*A copy of status.*/
    bool checked; /*A verification used in the DFS algorithm.*/
}cell_t;

/**
*@brief Allocates memory for a matrix of cell_t.
*@param rows Rows in matrix.
*@param cols Columns in matrix.
*@return A pointer to the new matrix.
*/
cell_t** create_matrix(int rows, int cols);

/**
*@brief Frees the memory used by matrix.
*@param matrix Matrix to be freed.
*@param rows Number of rows in matrix.
*/
void delete_matrix(cell_t** matrix, int rows);

/**
*@brief Prints the given matrix to stdout.
*@param matrix The matrix to be printed.
*@param rows Rows in matrix.
*@param cols Columns in matrix.
*/
void print_matrix(cell_t** matrix, int rows, int cols);

/**
*@brief Goes through the matrix and copies status to new_status.
*@param matrix The matrix to be modified.
*@param rows The amount of rows.
*@param cols The amount of cols.
*/
void copy_status(cell_t** matrix, int rows, int cols);

/**
*@brief Recursively searches the zone of a given char "status" in cell_t and returns its size.
*@param matrix The matrix to be searched.
*@param row Current row being used.
*@param col Current column being used.
*@param rows Number of rows in matrix.
*@param cols Number of columns in matrix.
*@param status The char "status" of the safe zone being searched.
*@return The size of the safe zone.
*/
int zone_checker(cell_t** matrix, int row, int col, int rows, int cols, char status);

/**
*@brief Goes through the matrix and when it finds a '-' calls zone_checker() to get the size of the zone. 
*@param matrix The matrix to be searched.
*@param rows Rows in matrix.
*@param cols Cols in matrix.
*@param status The char "status" of the safe zone being searched.
*@param safe_zone_count The amount of safe zones of the same size found.
*@return The size of the biggest safe zone found.
*/
int find_max_size(cell_t** matrix, int rows, int cols, char status, int* safe_zone_count);

/**
*@brief Goes through the matrix and sets the field checked to false.
*@param matrix The matrix to be searched.
*@param rows The amount of rows.
*@param cols The amount of cols.
*/
void reset_checked(cell_t** matrix, int rows, int cols);

/**
*@brief Resets checked with reset_checked() and goes through the matrix. If a status is equal to that given in the function it 
* checks if the zone is equal to the biggest and changes the current char "new_status" to new_status.
*@param matrix The matrix to be searched.
*@param rows The amount of rows.
*@param cols The amount of cols.
*@param biggest_size The biggest zone.
*@param status The char "status" of the safe zone being searched.
*@param new_status The char that replaces char "status".
*/
void change_status(cell_t** matrix, int rows, int cols, int biggest_size, char status, char new_status);

/**
*@brief Iterates through a matrix given in a file and sets the status of all elements of a desired matrix.
*@param argument The file to be read from.
*@param matrix The matrix which status values will be changed.
*@param rows The amount of rows.
*@param cols The amount of cols.
*/
void read_matrix(FILE* argument, cell_t** matrix, int rows, int cols);

/**
*@brief Prints a desired matrix in a specified output file
*@param matrix The matrix to be printed.
*@param rows The amount of rows.
*@param cols The amount of cols.
*@param safe_zones The amount of safe zones in the matrix after evaluating it.
*@param filename The name of the output file.
*/
void print_file_matrix(cell_t** matrix, int rows, int cols, int safe_zones, char* filename);

/**
*@brief Updates the corresponding status of matrix elements that are part of a safe zone
*@param matrix The matrix to be updated.
*@param rows The amount of rows.
*@param cols The amount of cols.
*/
int update_matrix(cell_t** matrix, int rows, int cols);

#endif //REFUGES_H