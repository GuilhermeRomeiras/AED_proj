#include <stdio.h>

#ifndef HEADER_H
#define HEADER_H
#define N_INICIAL 10




enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};

char *create_results_filename(char * filename_clients);

int read_file_map(FILE *file_map, int N, int L,
     int *cidade_part,int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);
int read_file_clients(FILE *file_clients);

void task1_func(int con_atual, int N, int L,  int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result);
void task2e3_func(int con_atual, int * compare, int N, int L, int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result);
void task4_func(int con_atual, int hora_inicial, int N, int L, 
     int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result, int *time, int *first, int *last, int *period);

void init_nodes(int N);
int nodes(int tmp_cp, int ntmp_cc, int con_atual);
void task5_func(int con_atual, int N, int *cidade1,  int *cidade2,  int *result);

void print_city (int L);
void print_arrays (int L, int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);

int Enum_str_to_int(const char *str);
const char* Enum_int_to_str(int transport_enum);
/*
//djynsky headers
typedef struct clients_file Item;
typedef struct _pq PQ;

PQ * PQinit(int); 
void PQinsert(PQ *, Item);
typedef int BOOL;
#define TRUE  1
#define FALSE 0

BOOL PQempty(PQ *);
//Item PQdelmax(PQ *); 
*/

void free_vectors_map(int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);
void free_cidades(int N);


#endif



