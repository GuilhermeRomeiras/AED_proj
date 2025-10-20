#ifndef FILE_results_c
#define FILE_results_c

#include <stdio.h>
#include "header.h"

void print_results(FILE *ptr_results_file, Sol* Solucao){
for (int i = 0; i < Solucao->caminho_size; i++)
{
fprintf(" %i ", Solucao->caminho[i]);
}
}
#endif