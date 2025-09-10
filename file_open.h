#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {AVIAO, COMBOIO, BARCO, AUTOCARRO}; 

typedef struct {
    int cidade_part;    // departure city (origem)
    int cidade_cheg;    // arrival city (destino)
    int automovel; // transport mode: aviao, comboio, barco, autocarro
    int cost;           // cost of the connection
    int time;           // duration time
    int first;          // first available time
    int last;           // last available time
    int period;         // period
} conn;


int read_file(const char* filename){
    char line[1024];
    
    FILE *file_map = fopen("test_file.csv", "r");

    if (!file_map) {
        perror("test_file.csv");
        fclose(file_map);
        return 1;
    }
    printf("File opened successfully!\n");


    int N, L;
    if (fscanf(file_map, "%d %d", &N, &L) != 2) {
        printf("Header error\n");
        fclose(file_map);
        return 1;
    }

    conn *connections = malloc(L * sizeof(conn));
    if (!connections) {
        printf("Memory error\n");   
        fclose(file_map);
        return 1;
    }

    printf("Cities: %d, Connections: %d\n", N, L);

    for (int i = 0; i < L; i++) {
        if (fscanf(file_map, "%d %d %s %d %d %d %d %d",                  
                   &connections[i].cidade_part,
                   &connections[i].cidade_cheg,
                   connections[i].automovel,
                   &connections[i].cost,
                   &connections[i].time,
                   &connections[i].first,
                   &connections[i].last,
                   &connections[i].period == 8)) {
            // Print each struct after reading
            printf("Connection %d:\n", i+1);
            printf("  cidade_part: %d\n", connections[i].cidade_part);
            printf("  cidade_cheg: %d\n", connections[i].cidade_cheg);
            printf("  automovel: %s\n", connections[i].automovel);
            printf("  cost: %d\n", connections[i].cost);
            printf("  time: %d\n", connections[i].time);
            printf("  first: %d\n", connections[i].first);
            printf("  last: %d\n", connections[i].last);
            printf("  period: %d\n\n", connections[i].period);
        } else {
            printf("Error reading line %d\n", i+1);
            break;
        }
    }

    free(connections);

    fclose(file_map);
    return 1;
}



