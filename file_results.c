#ifndef FILE_results_c
#define FILE_results_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "header.h"  // Para ter acesso às declarações
#include "global.h"


void results_file(char * filename_quests, int T, int *task, int *cidade1, int *cidade2, int *tempo_inicial, int *result){

const char* dot_pos = strrchr(filename_quests, '.');

// Verificar se encontrou o '.'
if (dot_pos == NULL) {
    //printf("Erro: ficheiro sem extensão\n");
    exit(0);
}

//printf("\n ok %s \n %s /n", dot_pos, filename_quests);

size_t prefix_length = dot_pos - filename_quests;

// Criar nome do ficheiro .results
char* results_filename = malloc(prefix_length + 10);


if (results_filename == NULL) {
   // printf("Erro: sem memória\n");
    free(results_filename);
    exit(0);
}

strncpy(results_filename, filename_quests, prefix_length);
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

for (int i = 0; i < T; i++){
        if (task[i] == 4){
            if (result[i] == -2){

            fprintf(ptr_results_file,"Task%d %i %i %i infinito\n\n",task[i], cidade1[i], cidade2[i], tempo_inicial[i]);
            }
            else
             fprintf(ptr_results_file,"Task%d %i %i %i %i\n\n",task[i], cidade1[i], cidade2[i], tempo_inicial[i], result[i]);
        }

        else
        {   if (result[i] == -2){
            fprintf(ptr_results_file,"Task%d %i %i infinito\n\n",task[i], cidade1[i], cidade2[i]);
        }
        else
        fprintf(ptr_results_file,"Task%d %i %i %i\n\n",task[i], cidade1[i], cidade2[i], result[i]);
    }
}
   
// close file
fclose(ptr_results_file);
free(results_filename);
results_filename = NULL;
}



#endif