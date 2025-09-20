
#ifndef FILE_OPEN_H
#define FILE_OPEN_H

#include "header.h"  // Para ter acesso às declarações


//funcao inicial que abre o ficheiro e armazena os dados em arrays que caracterizam, cada um, uma coluna do ficheiro .map
int read_file_map(const char* filename_map){
     
    // pointer para o ficheiro a ser aberto
    FILE *file_map = fopen(filename_map, "r");

    if (!file_map) {
        perror(filename_map);
        exit(0);
    }

    printf("File opened successfully!\n");
    
    // o fscanf para extrair o cabecalho
    if (fscanf(file_map, "%d %d", &N, &L) != 2) {
        printf("Header error\n");
        fclose(file_map);
        exit(0);
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
        free_vectors_map();
        fclose(file_map);
        exit(0);
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
            free_vectors_map();
            fclose(file_map);
            return 0;
        }
        n_con++;
        free(str);
    }

    printf("Successfully read %d right connections from %d total!\n", n_con, L);
    fclose(file_map);
    return 0; 

}



// Funcao que abre e analisa o ficheiro .quests
int read_file_quests(const char* filename_quests){ 

    // cast da funcao que abre o ficheiro e conta o nº de tasks
    int T = contar_tasks(filename_quests);
   
    task = malloc(T * sizeof(int));
    cidade1 = malloc(T * sizeof(int));
    cidade2 = malloc(T * sizeof(int));
    tempo_inicial = malloc(T * sizeof(int));
    result = malloc(T * sizeof(int));

    FILE *file_quests = fopen(filename_quests, "r");
    if (!file_quests) {
        perror(filename_quests);
        exit(0);
    }
    printf("File opened successfully again!\n");

    char *buffer;
    // loop for que le o ficheiro linha a linha incrementando i até T
    for (int i=0; i<T; i++){
        int tmp1=0, tmp2=0, tmp_ini=0;

        // se ler 1 string e 3 inteiros sabemos que é task4, armazenamos e damos cast da funcao que a resolve
        if (fscanf(file_quests, "%s %i %i %i", buffer, &tmp1, &tmp2, &tmp_ini) == 4){
            task[i] = 4;
            cidade1[i] = tmp1;
            cidade2[i] = tmp2;
            tempo_inicial[i] = tmp_ini;

            printf("Task 4\n");
            //task4_func(i);
        }
    
        // se ler 1 string e 2 inteiros, verificamos qual das tasks é, armazenamos e damos cast da sua funcao que a resolve
        else if (fscanf(file_quests, "%s %i %i", buffer, &tmp1, &tmp2) == 3){

            // task1
            if (strcmp(buffer, "Task1") == 0){
                task[i] = 1;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                task1_func(i);
                printf("Task 1 selected\n");
                
            }

            // task2
            else if (strcmp(buffer, "Task2") == 0){
                task[i] = 2;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 2 selected\n");
              //  task2_func(i);
            }

            // task3
            else if (strcmp(buffer, "Task3") == 0){
                task[i] = 3;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 3 selected\n");
              // task3_func(i);
            }

            // task5
            else if (strcmp(buffer, "Task5") == 0){
                task[i] = 5;
                cidade1[i] = tmp1;
                cidade2[i] = tmp2;

                printf("Task 5 selected\n");
               // task5_func(i);
            }
        }
        else if (fscanf(file_quests, "%s", buffer)) {
            strncmp(buffer, "Task", 4) != 0;
            printf("Data format error on line %d\n", i+1);
            continue;
        }
    }
    free(buffer);
    fclose(file_quests);
    return 0;

}



int contar_tasks(const char* filename_quests) {

    FILE *file_quests = fopen(filename_quests, "r");
    if (!file_quests) {
        perror(filename_quests);
        exit(0);
    }
    printf("File opened successfully!\n");
    
    int num_tasks = 0;
    char *token;
    
    // Lê token por token até ao fim do ficheiro
    while (fscanf(file_quests, "%ms", &token) == 1) {

        // Se o token começa com "Task", conta uma nova task
        if (strncmp(token, "Task", 4) == 0) {
            num_tasks++;
        }
    }

    fclose(file_quests);
    free(token);
    printf("File contains %d tasks\n", num_tasks);
    return num_tasks;

}


#endif