#include <stdio.h>
#include <stdlib.h>

#include "header.h"

// struct do tratamento de cidades
typedef struct cidades_adjacentes
{
    int *next_cidade;
    int *lig_id;

    int num_lig;
    int capacidade;
} adj;

adj *cidades;

int main(int argc, char *argv[])
{   
    int N = 0, L = 0;
    
    // verificar os comandos do terminal
    if (argc != 3)
    {
        // fprintf(stderr, "argument count is wrong\n");
        exit(0);
    }

    char *filename_map = argv[1];
    char *filename_quests = argv[2];

    // pointer para o ficheiro a ser aberto
    FILE *file_map = fopen(filename_map, "r");

    if (!file_map)
    {
        perror(filename_map);
        exit(0);
    }

    // printf("File opened successfully!\n");

    // o fscanf para extrair o cabecalho
    if (fscanf(file_map, "%d %d", &N, &L) != 2)
    {
        // printf("Header error\n");
        fclose(file_map);
        exit(0);
    }

    // armazenamento dinamico dos arrays map
   int *cidade_part = malloc(L * sizeof(int)); // coluna 1
   int *cidade_cheg = malloc(L * sizeof(int)); // coluna 2
   int *automovel = malloc(L * sizeof(int));   // coluna 3 (enum)
   int *time = malloc(L * sizeof(int));        // coluna 5
   int *cost = malloc(L * sizeof(int));        // coluna 4
   int *first = malloc(L * sizeof(int));       // coluna 6
   int *last = malloc(L * sizeof(int));        // coluna 7
   int *period = malloc(L * sizeof(int));      // coluna 8

    // cast da funcao que abre o ficheiro e conta o nº de tasks
    int T = contar_tasks(filename_quests);

    // armazenamento dinamico dos arrays tasks
    int *task = malloc(T * sizeof(int));
    int *cidade1 = malloc(T * sizeof(int));
    int *cidade2 = malloc(T * sizeof(int));
    int *tempo_inicial = malloc(T * sizeof(int));
    int *result = calloc(T, sizeof(int));

    read_file_map(filename_map, file_map, N, L,
     cidade_part,cidade_cheg, automovel, time, cost, first, last, period);
    read_file_quests(filename_quests, T, N, L, cidade_part, cidade_cheg, first, last, period,
     task, cidade1, cidade2, tempo_inicial, result, time, cost);

    // print_arrays();

    /*for (int i=0; i<T; i++)
    printf("%i\n", result[i]);*/

    results_file(filename_quests, T, task, cidade1, cidade2, tempo_inicial, result);
    
    
    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors_map(cidade_part, cidade_cheg, automovel, time, cost, first, last, period);
    free_vectors_quests(task, cidade1, cidade2, tempo_inicial, result);
    free_cidades(N);


    return 0;
}