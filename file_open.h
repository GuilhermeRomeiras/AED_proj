#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "header.h"  // Para ter acesso às declarações



//funcao inicial que abre o ficheiro e armazena os dados em arrays que caracterizam, cada um, uma coluna do ficheiro .map
int read_file_map(const char* filename){
     
    FILE *file_map = fopen(filename, "r");

    if (!file_map) {
        perror(filename);
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
                    
            tmp_aut = Enum_str_to_int(str, i);

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
        }

        else {
            printf("Data format error on line %d\n", i+2);
            free(str);
            free_vectors();
            fclose(file_map);
            return 0;
        }
        n_con++;
        free(str);
    }

    printf("Successfully read %d connections\n", n_con);
    fclose(file_map);
    return 0; 

}



int read_file_quests(const char* filename){ 
    
    FILE *file_map = fopen(filename, "r");

    if (!file_map) {
        perror(filename);
        return 0;
    }

     char **task = malloc(5 * sizeof(char*));

    cidade1 = malloc(L * sizeof(int));
    cidade2 = malloc(L * sizeof(int));
    tempo_inicial = malloc(L * sizeof(int));

    for (int i=0; i<L; i++){
        if (fscanf(file_map, "%ms %i %i %i", buffer, tmp1, tmp2, tmp_ini) = 4){
            task[i] = buffer;
            cidade1[i] = tmp1;
            cidade2[i] = tmp2;
            tempo_inicial[i] = tmp_ini;

            printf("Task 4 selected\n");
            task4_func();
        }
    
        else if (fscanf(file_map, "%ms %i %i %i", buffer, cidade1, cidade2) = 3){

            if (buffer == "Task1"){
                task[i] = buffer;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 1 selected\n");
                task1_func();
            }

            else if (buffer == "Task2"){
                task[i] = buffer;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 2 selected\n");
                task2_func();
            }

            else if (buffer == "Task3"){
                task[i] = buffer;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 3 selected\n");
                task3_func();
            }

            else if (buffer == "Task5"){
                task[i] = buffer;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 5 selected\n");
                task5_func();
            }
        }
    }
    printf("argument received: %s\n", buffer);
    printf("File opened successfully!\n");

    free(buffer);
    fclose(file_map);
    return 0;
    
}


#endif