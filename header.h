#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};
int N, L;
int *cidade_part, *cidade_cheg, *automovel, *cost, *time, *first, *last, *period;
int *task, *cidade1, *cidade2, *tempo_inicial, *result;

int read_file_map(const char* filename_map);
int read_file_quests(FILE* file_quests, int T);
int contar_tasks(const char* filename_quests);

void task1_func(int con_atual);

void print_arrays(void);

int Enum_str_to_int(const char *str, int num_con_err);
const char* Enum_int_to_str(int transport_enum);
void free_vectors_map(void);
void free_vectors_quests(void);

#endif

