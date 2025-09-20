#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"
#include "file_open.c"
#include "aux_functions.c"
#include "task_functions.c"


int main(int argc, char *argv[]) {

    if (argc != 3) {
       fprintf(stderr, "argument count is wrong\n");
       exit(0);
    }
    
    char *filename_map = argv[1];
    char *filename_quests = argv[2];
    
     // cast da funcao que abre o ficheiro e conta o nº de tasks
    int T = contar_tasks(filename_quests);

    task = malloc(T * sizeof(int));
    cidade1 = malloc(T * sizeof(int));
    cidade2 = malloc(T * sizeof(int));
    tempo_inicial = malloc(T * sizeof(int));
    result = malloc(T * sizeof(int));

    FILE *file_quests = fopen(filename_quests, "r");
    if (!file_quests) {
        perror(filename_quests);
        exit(0);
    }
    printf("File opened successfully again!\n");

    read_file_map(filename_map);  
    read_file_quests(file_quests, T);
    //print_arrays();

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors_map();
    free_vectors_quests();

    return 0;
}