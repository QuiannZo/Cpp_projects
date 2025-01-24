#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "refuges.h"

// Updates matrix with corresponding R values and also returns the amount of refuge zones (safe_zones)
int update_matrix(cell_t** matrix, int rows, int cols);

int main(int argc, char* argv[]) {
    int rows = 0, cols = 0, safe_zones = 0;
    char* filename;
    char* outputfilename;
    cell_t** matrix;
    // If argument count in terminal > 1, use filename provided to open file
    if (argc == 3) {
        // If file is a text file
        if (strcmp(argv[1], "-f") == 0) {
            filename = argv[2];
            outputfilename = malloc(strlen(filename) + 5); // +5 because "-out\0" is 5 extra characters
            sprintf(outputfilename, "%s-out", filename); // append -out to filename and store result in outputfilename
            FILE* argument = fopen(filename, "r");
            if (argument == NULL) {
                printf("Error: Could not open file '%s'\n", filename);
                return EXIT_FAILURE;
            }
            // Scan for rows and cols
            fscanf(argument, "%d %d\n", &rows, &cols);
            // Create matrix
            matrix = create_matrix(rows, cols);
            // Init matrix
            read_matrix(argument, matrix, rows, cols);
            // Update refuge zones with 'R'
            safe_zones = update_matrix(matrix, rows, cols);
            // Print the matrix using an output file
            print_file_matrix(matrix, rows, cols, safe_zones, outputfilename);
            fclose(argument);
            free(outputfilename);
        } // If file is binary
        else if (strcmp(argv[1], "-b") == 0) {
            filename = argv[2];
            FILE* argument = fopen(filename, "rb");
            outputfilename = malloc(strlen(filename) + 5);
            sprintf(outputfilename, "%s-out", filename);
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
                    // Store found char on matrix, if char isn't found then show error
                    if (fread(&matrix[row][col].status, sizeof(char), 1, argument) != 1) {
                        printf("Error: Could not read matrix from binary file\n");
                        fclose(argument);
                        delete_matrix(matrix, rows);
                        return EXIT_FAILURE;
                    }
                }
            }
            safe_zones = update_matrix(matrix, rows, cols);
            print_file_matrix(matrix, rows, cols, safe_zones, outputfilename);
            fclose(argument);
            free(outputfilename);
        }
        else {
            printf("Usage: %s 'flag' 'filename' (-f for file | -b for binary)\n", argv[0]);
            return EXIT_FAILURE;
        }
        
    } else if (argc == 1) { // Else use stdin for input
        printf("Please enter the number of rows and columns followed by the matrix\n");
        scanf("%d %d\n", &rows, &cols);
        matrix = create_matrix(rows, cols);
        read_matrix(stdin, matrix, rows, cols);
        safe_zones = update_matrix(matrix, rows, cols);
        printf("%d\n", safe_zones);
        print_matrix(matrix, rows, cols);
    }
    else {
        printf("Invalid command-line arguments\n");
        return EXIT_FAILURE;
    }
    delete_matrix(matrix, rows);
}
