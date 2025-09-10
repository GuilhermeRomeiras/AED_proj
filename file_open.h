#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {AVIAO, COMBOIO, BARCO, AUTOCARRO, n_transport_modes};

typedef struct {
    int cidade_part;    // departure city (origem)
    int cidade_cheg;    // arrival city (destino)
    int automovel;      // transport mode: aviao, comboio, barco, autocarro
    int cost;           // cost of the connection
    int time;           // duration time
    int first;          // first available time
    int last;           // last available time
    int period;         // period
} conn;


int read_file(const char* filename){
    char *str_enum[] = {"aviao", "comboio", "barco", "autocarro"};
    char line[1024];
    char buffer [10];   
    
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
        return -1;
    }

    printf("Cities: %d, Connections: %d\n", N, L);

        int i=0;
        while (fscanf(file_map, "%d %d %s %d %d %d %d %d",
                   &connections[i].cidade_part,
                   &connections[i].cidade_cheg,
                   buffer,
                   &connections[i].cost,
                   &connections[i].time,
                   &connections[i].first,
                   &connections[i].last,
                   &connections[i].period) == 8) {


                if (strcmp(buffer,"aviao") == 0){ 
                    connections[i].automovel = AVIAO;
                }

                else if (strcmp(buffer,"comboio") == 0){ 
                    connections[i].automovel = COMBOIO;
                }

                else if (strcmp(buffer,"barco") == 0){ 
                    connections[i].automovel = BARCO;
                }

                else if (strcmp(buffer,"autocarro") == 0){ 
                    connections[i].automovel = AUTOCARRO;
                 }


                 printf("Connection %d:\n", i+1);
            printf("  cidade_part: %d\n", connections[i].cidade_part);
            printf("  cidade_cheg: %d\n", connections[i].cidade_cheg);
            printf("  automovel: %s\n", buffer);
            printf("  cost: %d\n", connections[i].cost);
            printf("  time: %d\n", connections[i].time);
            printf("  first: %d\n", connections[i].first);
            printf("  last: %d\n", connections[i].last);
            printf("  period: %d\n\n", connections[i].period);
            

            i++;

            }
    free(connections);

    fclose(file_map);
    return 0;
}

/*void print_connections(conn* connections, int L){
            
    int j=0;
            while (j < L)
            {
                   
            printf("Connection %d:\n", j+1);
            printf("  cidade_part: %d\n", connections[j].cidade_part);
            printf("  cidade_cheg: %d\n", connections[j].cidade_cheg);
            printf("  automovel: %d\n", connections[j].automovel);
            printf("  cost: %d\n", connections[j].cost);
            printf("  time: %d\n", connections[j].time);
            printf("  first: %d\n", connections[j].first);
            printf("  last: %d\n", connections[j].last);
            printf("  period: %d\n\n", connections[j].period);
            j++;
        
        }
    }
*/


