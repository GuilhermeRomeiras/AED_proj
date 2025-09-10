#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int cidade_part;    // departure city (origem)
    int cidade_cheg;    // arrival city (destino)
    char automovel[5]; // transport mode: aviao, comboio, barco, autocarro
    int cost;           // cost of the connection
    int time;           // duration time
    int first;          // first available time
    int last;           // last available time
    int period;         // period
} conn;

typedef struct {
    int num_cities;
    int num_connections;
    conn* connections;  // dynamic array of connections
} transport_data;

int read_file(const char* filename){
    conn connection;
    char line[1024];
    int N, L;
    
    FILE *file_map = fopen("test_file.csv", "r");

    if (file_map == NULL) {
        printf("Error!\n");
        return 1;
    }
    printf("File opened successfully!\n");

       if (fscanf(file_map, "%d %d", &N, &L) != 2) {
       printf("Error reading header\n");
   }

    printf("Cities: %d, Connections: %d\n", N, L);

    for (int i = 0; i < L; i++) {
        if (fscanf(file_map, "%d %d %s %d %d %d %d %d", 
                   &connection.cidade_part, &connection.cidade_cheg, connection.automovel,
                   &connection.cost, &connection.time, &connection.first, &connection.last, &connection.period) == 8) {
           
            printf("All data received:\n");
        } else {
            printf("Error reading connection %d\n", i + 1);
            break;
        }
    }

    fclose(file_map);
    return 1;
}


// Function declarations
transport_data* read_file(const char* filename);
void free_transport_data(transport_data* data);
void print_connections(transport_data* data);

// Read file and return all data in a structure
transport_data* read_file(const char* filename) {
    FILE *file_map = fopen(filename, "r");
    
    if (file_map == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    
    printf("File opened successfully!\n");
    
    // Allocate memory for the transport_data structure
    transport_data* data = (transport_data*)malloc(sizeof(transport_data));
    if (data == NULL) {
        printf("Memory allocation error!\n");
        fclose(file_map);
        return NULL;
    }
    
    // Read the header (number of cities and connections)
    if (fscanf(file_map, "%d %d", &data->num_cities, &data->num_connections) != 2) {
        printf("Error reading header\n");
        free(data);
        fclose(file_map);
        return NULL;
    }
    
    printf("Cities: %d, Connections: %d\n", data->num_cities, data->num_connections);
    
    // Allocate memory for the connections array
    data->connections = (conn*)malloc(data->num_connections * sizeof(conn));
    if (data->connections == NULL) {
        printf("Memory allocation error for connections!\n");
        free(data);
        fclose(file_map);
        return NULL;
    }
    
    // Read each connection and store it in the array
    for (int i = 0; i < data->num_connections; i++) {
        if (fscanf(file_map, "%d %d %4s %d %d %d %d %d", 
                   &data->connections[i].cidade_part, 
                   &data->connections[i].cidade_cheg, 
                   data->connections[i].automovel,
                   &data->connections[i].cost, 
                   &data->connections[i].time, 
                   &data->connections[i].first, 
                   &data->connections[i].last, 
                   &data->connections[i].period) == 8) {
            
            printf("Successfully read connection %d: %d -> %d via %s\n", 
                   i + 1, data->connections[i].cidade_part, 
                   data->connections[i].cidade_cheg, data->connections[i].automovel);
        } else {
            printf("Error reading connection %d\n", i + 1);
            // Clean up and return NULL on error
            free(data->connections);
            free(data);
            fclose(file_map);
            return NULL;
        }
    }
    
    fclose(file_map);
    return data;  // Return the populated data structure
}

// Function to free allocated memory
void free_transport_data(transport_data* data) {
    if (data != NULL) {
        if (data->connections != NULL) {
            free(data->connections);
        }
        free(data);
    }

}

// Function to print all connections (for debugging/verification)
void print_connections(transport_data* data) {
    if (data == NULL) {
        printf("No data to print\n");
        return;
    }
    
    printf("\n=== Transport Network Data ===\n");
    printf("Cities: %d, Connections: %d\n\n", data->num_cities, data->num_connections);
    
    for (int i = 0; i < data->num_connections; i++) {
        printf("Connection %d:\n", i + 1);
        printf("  From city %d to city %d\n", 
               data->connections[i].cidade_part, data->connections[i].cidade_cheg);
        printf("  Transport: %s\n", data->connections[i].automovel);
        printf("  Cost: %d, Time: %d\n", 
               data->connections[i].cost, data->connections[i].time);
        printf("  Available: %d to %d, Period: %d\n\n", 
               data->connections[i].first, data->connections[i].last, data->connections[i].period);
    }
}

