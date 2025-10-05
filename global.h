#ifndef GLOBAL_H
#define GLOBAL_H

// struct do tratamento de cidades
typedef struct cidades_adjacentes
{
    int *next_cidade;
    int *lig_id;

    int num_lig;
    int capacidade;
} adj;
extern adj *cidades;



#endif