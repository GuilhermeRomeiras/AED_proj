#include <stdio.h>

#ifndef HEADER_H
#define HEADER_H
#define N_INICIAL 10

// Define all structs in header

// struct do tratamento de cidades
typedef struct cidades_adjacentes
{
    int *next_cidade;
    int *lig_id;

    int num_lig;
    int capacidade ;
} adj;

typedef struct Restricoes {
    int meio_proibido; //A1
    int max_tempo_ligacao; //A2
    int max_custo_ligacao; //A3
    int max_tempo_total; //B1
    int max_custo_total; //B2
} Restricoes;

typedef struct Cliente {
    int id;
    int cidade_origem;
    int cidade_destino;
    int tempo_inicial;
    char preferencia;
    int num_restricoes;
    Restricoes rest;  // Not a pointer, embedded struct
} Cli;


typedef struct Solucao {
    int id;
    int valida;
    int codigo_erro;
    int *caminho;
    int caminho_size;
    int tempo_total;
    int custo_total;
} Sol;


enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};

char *create_results_filename(char * filename_clients);

int read_file_map(FILE *file_map, int N, int L,
     int *cidade_part,int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period, adj *cidades);
int read_file_clients(FILE *file_clients, Cli* p_clients_file, Restricoes *Restricoes);

void function_case(FILE *file_clients, Restricoes *rest, int client_id);

void dijkstra(adj *cidades, Cli *cliente, Sol *Solucao, int N,
              int *time, int *cost);

void task1_func(int con_atual, int N, int L,  int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result);
void task2e3_func(int con_atual, int * compare, int N, int L, int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result);
void task4_func(int con_atual, int hora_inicial, int N, int L, 
     int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result, int *time, int *first, int *last, int *period);

void init_nodes(int N, adj *cidades);
int nodes(int tmp_cp, int ntmp_cc, int con_atual, adj *cidades);
void task5_func(int con_atual, int N, int *cidade1,  int *cidade2,  int *result);

void print_city (int L, adj *cidades);
void print_arrays (int L, int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);

int Enum_str_to_int(const char *str);
const char* Enum_int_to_str(int transport_enum);


void free_vectors_map(int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);
void free_cidades(int N, adj *cidades);


#endif



