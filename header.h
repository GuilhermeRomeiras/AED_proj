#ifndef HEADER_H
#define HEADER_H

enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};

int read_file_map(const char* filename_map);
int read_file_quests(char* filename_quests, int T);
int contar_tasks(const char* filename_quests);

void task1_func(int con_atual);
void task2e3_func(int con_atual, int *compare);
void task4_func(int con_atual, int hora_inicial);
void task5_func(int con_atual);

void print_arrays(void);

int Enum_str_to_int(const char *str, int num_con_err);
const char* Enum_int_to_str(int transport_enum);

void results_file(char * filename_quests, int T);

void free_vectors_map(void);
void free_vectors_quests(void);

#endif



