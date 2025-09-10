#include <stdio.h>
#include "file_open.h"

 // Example usage in main function
int main() {
    // Read the data from file
    read_file("test_file.csv");

    if (data != NULL) {
        printf("Data loaded successfully!\n");

        // Print all connections to verify
        print_connections(data);     

        // Don't forget to free the memory when done
        free_transport_data(data);
    } else {
        printf("Failed to load data from file\n");
    }

    return 0;
 }

