#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file_map(const char* filename);
int read_file_quests(const char* filename);

void print_arrays(int *cidade_part, int *cidade_cheg, int *automovel, 
                  int *cost, int *time, int *first, int *last, int *period, int L);

int Enum_str_to_int(const char *str, int num_con_err);
const char* Enum_int_to_str(int transport_enum);
void free_vectors(void);

#endif
