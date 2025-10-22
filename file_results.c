#ifndef FILE_results_c
#define FILE_results_c

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void print_results(FILE *ptr_results_file, Node *solution, int n_nodes, int *automovel, Cli cliente){
    if(solution){
        fprintf(ptr_results_file, "%i ", cliente.id);
        fprintf(ptr_results_file, "%i ", solution[0].city_idx+1);
        for (int i = 1; i < n_nodes; i++){
            fprintf(ptr_results_file, "%s %i ", Enum_int_to_str(automovel[solution[i].lig_id]), solution[i].city_idx+1);
        }
        fprintf(ptr_results_file, "%i %i\n", solution[n_nodes-1].arrival_time-cliente.tempo_inicial, solution[n_nodes-1].cost);
    } else
        fprintf(ptr_results_file, "%i -1\n", cliente.id);

}

#endif
