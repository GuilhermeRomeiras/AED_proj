#ifndef FILE_results_c
#define FILE_results_c

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void print_results(FILE *ptr_results_file, Sol *Solucao, int *automovel, Cli *cliente){
if(Solucao->valida == 1){
        fprintf(ptr_results_file, "%i ", cliente->id);
        for (int i = 0; i < Solucao->caminho_size; i++){
            fprintf(ptr_results_file, "%i %s ", Solucao->caminho[i]+1, Enum_int_to_str(automovel[Solucao->caminho_id[i]]));
        }
        fprintf(ptr_results_file,"%i ", cliente->cidade_destino + 1);
        fprintf(ptr_results_file, "%i %i\n", Solucao->tempo_total, Solucao->custo_total);
    }
    else
    {
        fprintf(ptr_results_file, "%i -1\n", cliente->id);
    }
    
    
free(Solucao->caminho_id);
free(Solucao->caminho);

}

#endif