#ifndef FILE_results_c
#define FILE_results_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"  // Para ter acesso às declarações
#include "global.h"


void results_file(char * filename_quests){

const char* dot_pos = strrchr(filename_quests, '.');

// Verificar se encontrou o '.'
if (dot_pos == NULL) {
    printf("Erro: ficheiro sem extensão\n");
    exit(0);
}

printf("\n ok %s \n", dot_pos);
printf("\n %s \n", filename_quests);

size_t prefix_length = dot_pos - filename_quests;

printf("\n kfklfa %ld \n", prefix_length);

// Criar nome do ficheiro .results
char* results_filename = malloc(prefix_length + 10);

// Verificar se malloc funcionou
if (results_filename == NULL) {
    printf("Erro: sem memória\n");
    exit(0);
}

results_filename[prefix_length] = '\0';
strcat(results_filename, ".results");

// Usar no fprintf
FILE* ptr_results_file = fopen(results_filename, "w");


if (!ptr_results_file) {
        perror("test.results");
        fclose(ptr_results_file);
        free(results_filename);
        exit(0);
    }

for (int i = 0; result != NULL; i++){

        fprintf(ptr_results_file ,"%i ", result[i]);
}
   
// close file
fclose(ptr_results_file);
free(results_filename);
}



#endif