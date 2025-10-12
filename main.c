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
    char *filename_clients = argv[2];
    char *results_filename = create_results_filename(filename_clients);

    // pointer para o ficheiro a ser aberto
    FILE *file_map = fopen(filename_map, "r");

    if (!file_map)
    {
        perror(filename_map);
        exit(0);
    }

    FILE *file_clients = fopen(filename_clients, "r");
    if (!file_clients)
    {
        perror(filename_clients);
        exit(0);
    }
    
    FILE* ptr_results_file = fopen(results_filename, "w");
    if (!ptr_results_file)
    {
        perror(results_filename);
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
   // int T = contar_clients(filename_clients);

    read_file_map(file_map, N, L,
     cidade_part,cidade_cheg, automovel, time, cost, first, last, period);

    read_file_clients(file_clients);
    // print_arrays();

   fclose(file_clients);

    // close results file
    fclose(ptr_results_file);

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors_map(cidade_part, cidade_cheg, automovel, time, cost, first, last, period);

  //  free_vectors_quests(task, cidade1, cidade2, tempo_inicial, result);
    free(results_filename);
    free_cidades(N);
    free(results_filename);

    return 0;
}