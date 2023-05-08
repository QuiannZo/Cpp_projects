#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "refuges.h"

int main(int argc, char* argv[]) {
    int rows = 0, cols = 0;
    char* filename;
    cell_t** matrix;
    // If argument count in terminal > 1, use filename provided to open file
    if (argc > 1) {
        // If file is a text file
        if (strcmp(argv[1], "-f") == 0) {
            filename = argv[2];
            FILE* argument = fopen(filename, "r");
            if (argument == NULL) {
                printf("Error: Could not open file '%s'\n", filename);
                return EXIT_FAILURE;
            }
            fscanf(argument, "%d %d\n", &rows, &cols);
            matrix = create_matrix(rows, cols);
            read_matrix(argument, matrix, rows, cols);
            fclose(argument);
        } // If file is binary
        else if (strcmp(argv[1], "-b") == 0) {
            filename = argv[2];
            FILE* argument = fopen(filename, "rb");
            if (argument == NULL) {
                printf("Error: Could not open file '%s'\n", filename);
                return EXIT_FAILURE;
            }
            fread(&rows, sizeof(int), 1, argument);
            fread(&cols, sizeof(int), 1, argument);
            matrix = create_matrix(rows, cols);
            // Initialize the matrix using a binary file
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    if (fread(&matrix[row][col].status, sizeof(char), 1, argument) != 1) {
                        printf("Error: Could not read matrix from binary file\n");
                        fclose(argument);
                        delete_matrix(matrix, rows);
                        return EXIT_FAILURE;
                    }
                }
            }
            fclose(argument);
        }
        else {
            printf("Usage: %s 'flag' 'filename' (-f for file | -b for binary)\n", argv[0]);
            return EXIT_FAILURE;
        }
        
    } else { // Else use stdin for input
        printf("Please enter the number of rows and columns:\n");
        scanf("%d %d\n", &rows, &cols);
        matrix = create_matrix(rows, cols);
        read_matrix(stdin, matrix, rows, cols);
    }
    cpy_status(matrix, rows, cols);
    int safe_zones = 0;
    int max_size = find_max_size(matrix, rows, cols, '-', &safe_zones);
    change_status(matrix, rows, cols, max_size, '-', 'R');
    printf("%d\n", safe_zones);
    print_matrix(matrix, rows, cols);
    delete_matrix(matrix, rows);
}
