#include <stdio.h>
#include "file_open.h"


int main() {

printf("Starting file reading program...\n\n");
    
    // Read the CSV file using the line-by-line approach
    printf("=== Reading CSV file line by line ===\n");
    if (read_file("test_file.csv") != 0) {
        printf("Failed to read the file\n");
        return 1;
    }
    
    printf("\nProgram completed successfully!\n");

return 0;
}

