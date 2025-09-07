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

int read_file(const char* filename);

int read_file(const char* filename){
    conn connection;
    char line[1024];

    FILE *file_map = fopen("test_file.csv", "r");

    if (file_map == NULL) {
        printf("Error!\n");
        return 1;
    }
    printf("File opened successfully!\n");

     int N, L;
       if (fscanf(file_map, "%d %d", &N, &L) != 2) {
       printf("Error reading header\n");
   }

    printf("Cities: %d, Connections: %d\n", N, L);

    for (int i = 0; i < L; i++) {
        if (fscanf(file_map, "%d %d %s %d %d %d %d %d", 
                   &connection.cidade_part, &connection.cidade_cheg, connection.automovel,
                   &connection.cost, &connection.time, &connection.first, &connection.last, &connection.period) == 8) {
           
            printf("Connection %d:\n", i + 1);
        } else {
            printf("Error reading connection %d\n", i + 1);
            break;
        }
    }

    fclose(file_map);
    return 1;
}





