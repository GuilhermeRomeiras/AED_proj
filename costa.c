#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};
int N, L;


int *cidade_part, *cidade_cheg, *automovel, *cost, *time, *first, *last, *period;
int Enum_str_to_int(const char *str);
const char* Enum_int_to_str(int transport_enum);
void free_vectors(void);
void free_tmps(void);



//funcao inicial que abre o ficheiro e armazena os dados em arrays que caracterizam, cada um, uma coluna do ficheiro .map
int read_file_map(const char* filename){
     
    filename = "map.csv";
    FILE *file_map = fopen("map.csv", "r");

    if (!file_map) {
        perror("map.csv");
        return 0;
    }

    printf("File opened successfully!\n");
    
    if (fscanf(file_map, "%d %d", &N, &L) != 2) {
        printf("Header error\n");
        fclose(file_map);
        return 0;
    }
    
    printf("Cities: %d, Connections: %d\n", N, L);
    
    // Declarar arrays para cada coluna
    cidade_part = malloc(L * sizeof(int));     // coluna 1
    cidade_cheg = malloc(L * sizeof(int));     // coluna 2
    automovel = malloc(L * sizeof(int));       // coluna 3 (enum)
    cost = malloc(L * sizeof(int));            // coluna 4
    time = malloc(L * sizeof(int));            // coluna 5
    first = malloc(L * sizeof(int));           // coluna 6
    last = malloc(L * sizeof(int));            // coluna 7
    period = malloc(L * sizeof(int));          // coluna 8
    
    // Verificar se todos os malloc foram bem sucedidos
    if (!cidade_part || !cidade_cheg || !automovel || !cost || !time || !first || !last || !period) {
        printf("Memory error\n");

        // Libertar memoria ja alocada
        free_vectors();
        fclose(file_map);
        return 0;
    }
    
    int n_con = 0; // Contador de conexoes lidas com sucesso
    for (int i=0; i<L; i++){
        char *str = NULL;
        int tmp_cp, tmp_cc, tmp_cost, tmp_time, tmp_first, tmp_last, tmp_p, tmp_aut;

        if (fscanf(file_map, "%d %d %ms %d %d %d %d %d",
                   &tmp_cp,
                   &tmp_cc,
                   &str,
                   &tmp_cost,
                   &tmp_time,
                   &tmp_first,
                   &tmp_last,
                   &tmp_p) == 8){

            tmp_aut = Enum_str_to_int(str);

            if (tmp_aut == 0){
                continue;
            }

            cidade_part[i] = tmp_cp;
            cidade_cheg[i] = tmp_cc;
            automovel[i] = tmp_aut;
            cost[i] = tmp_cost;
            time[i] = tmp_time;
            first[i] = tmp_first;
            last[i] = tmp_last;
            period[i] = tmp_p;

            n_con++;
        }

        else {
            printf("Data format error on line %d\n", i+2);
            free(str);
            free_vectors();
            fclose(file_map);
            return 0;
        }
    
        free(str);
    }

    printf("Successfully read %d connections\n", n_con);
    fclose(file_map);
    free(filename);
    filename = NULL;
    return 0; 

}



read_file_quests(const char* filename){

    filename = "test.quests";
    FILE *file_map = fopen("test.quests", "r");

    if (!file_map) {
        perror("test.quests");
        return 0;
    }

    printf("File opened successfully!\n");
    
}



// Funcao auxiliar para imprimir os dados dos arrays
void print_arrays(int *cidade_part, int *cidade_cheg, int *automovel, 
                  int *cost, int *time, int *first, int *last, int *period, int L) {

    printf("\n=== Array Data ===\n");
    for (int i = 0; i < L; i++) {
        const char *mode_str = Enum_int_to_str(automovel[i]);

        printf("Connection %d:\n", i+1);
        printf("  cidade_part: %d\n", cidade_part[i]);
        printf("  cidade_cheg: %d\n", cidade_cheg[i]);
        printf("  automovel: %s (%d)\n", mode_str, automovel[i]);
        printf("  cost: %d\n", cost[i]);
        printf("  time: %d\n", time[i]);
        printf("  first: %d\n", first[i]);
        printf("  last: %d\n", last[i]);
        printf("  period: %d\n\n", period[i]);
    }

}



// Funcao que transforma a string do ficheiro em inteiro para melhor manipulacao
int Enum_str_to_int(const char *str){

    if (strcmp(str, "aviao") == 0) return AVIAO;
    else if (strcmp(str, "comboio") == 0) return COMBOIO;
    else if (strcmp(str, "barco") == 0) return BARCO;
    else if (strcmp(str, "autocarro") == 0) return AUTOCARRO;
    else {
        printf("Invalid transportation");
        return 0; // Retorna 0 para transporte invalido
    }

}


// Funcao inversa que transforma o inteiro de volta para string para dar print ou escrever no ficheiro de saida. O parametro transport_enum Ã© extraido,
// quando necessario, do valor automovel(i) que se queira escrever fazendo transport_enum = automovel(i) e de seguida chamando esta funcao
const char* Enum_int_to_str(int transport_enum){ 

    switch(transport_enum) {
        case AVIAO:     return "aviao";
        case COMBOIO:   return "comboio";
        case BARCO:     return "barco";
        case AUTOCARRO: return "autocarro";
        default:        return "incorrect transport";
    }

}



int main() {

    read_file_map("map.csv");
    print_arrays(cidade_part, cidade_cheg, automovel, cost, time, first, last, period, L);

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors();

    return 0;

}



void free_vectors(void) {

    free(cidade_part);
        cidade_part = NULL;

    free(cidade_cheg); 
        cidade_cheg = NULL; 

    free(automovel);
       automovel = NULL; 

    free(cost);
        cost = NULL; 

    free(time);
        time = NULL;   

    free(first);
       first = NULL;

    free(last);
        last = NULL; 

    free(period);
        period = NULL; 

}
