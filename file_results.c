#ifndef FILE_results_c
#define FILE_results_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"  // Para ter acesso às declarações
#include "global.h"


char *create_results_filename(char * filename_clients){

const char* dot_pos = strrchr(filename_clients, '.');

// Verificar se encontrou o '.'
if (dot_pos == NULL) {
    //printf("Erro: ficheiro sem extensão\n");
    exit(0);
}

//printf("\n ok %s \n %s /n", dot_pos, filename_quests);
size_t prefix_length = dot_pos - filename_clients;

// Criar nome do ficheiro .results
char* results_filename = malloc(prefix_length + 10);

if (results_filename == NULL) {
   // printf("Erro: sem memória\n");
    free(results_filename);
    exit(0);
}

strncpy(results_filename, filename_clients, prefix_length);
results_filename[prefix_length] = '\0';
strcat(results_filename, ".sol");

return results_filename;
}



#endif