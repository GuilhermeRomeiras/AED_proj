#ifndef HEADER_H
#define HEADER_H
#define N_INICIAL 20
#define N_BYTES 1024


enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};

int read_file_map(const char *filename_map, int N, int L,
     int *cidade_part,int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);
int read_file_quests(char *filename_quests, int T, int N, int L, int *cidade_part, int *cidade_cheg, int *first, int *last, int *period,
     int *task, int *cidade1, int *cidade2, int *tempo_inicial, int *result, int *time, int *cost);

int contar_tasks(const char* filename_quests);

void task1_func(int con_atual, int N, int L,  int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result);
void task2e3_func(int con_atual, int * compare, int N, int L, int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result);
void task4_func(int con_atual, int hora_inicial, int N, int L, int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result, int *time, int *first, int *last, int *period);
void init_nodes(int N);
int nodes(int next_cidade, int lig_id);
void task5_func(int con_atual, int N, int *cidade1,  int *cidade2,  int *result);

void print_arrays (int L, int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);

int Enum_str_to_int(const char *str, int num_con_err);
const char* Enum_int_to_str(int transport_enum);

void results_file(char * filename_quests, int T, int *task, int *cidade1, int *cidade2, int *tempo_inicial, int *result);

void free_vectors_map(int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period);
void free_vectors_quests(int *task, int *cidade1, int *cidade2, int *tempo_inicial, int *result);

#endif



