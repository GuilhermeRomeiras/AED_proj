#include <stdio.h>
#include <stdlib.h>

#include "header.h"


int N, L;
int *cidade_part, *cidade_cheg, *automovel, *time, *cost, *first, *last, *period;
int *task, *cidade1, *cidade2, *tempo_inicial, *result;



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
    result = calloc(T, sizeof(int));
    

    read_file_map(filename_map);  
    read_file_quests(filename_quests, T);
    //print_arrays();

    for (int i=0; i<T; i++)
    printf("%i\n", result[i]);

    results_file(filename_quests);

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors_map();
    free_vectors_quests();

    return 0;
}