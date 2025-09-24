
#ifndef FILE_OPEN_H
#define FILE_OPEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"  // Para ter acesso às declarações
#include "global.h"

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
    time = malloc(L * sizeof(int));            // coluna 5
    cost = malloc(L * sizeof(int));            // coluna 4
    first = malloc(L * sizeof(int));           // coluna 6
    last = malloc(L * sizeof(int));            // coluna 7
    period = malloc(L * sizeof(int));          // coluna 8
    
    // Verificar se todos os malloc foram bem sucedidos
    if (!cidade_part || !cidade_cheg || !automovel || !time || !cost || !first || !last || !period) {
        printf("Memory error\n");

        // Libertar memoria ja alocada
        free_vectors_map();
        fclose(file_map);
        exit(0);
    }
    
    int n_con = 0; // Contador de conexoes lidas com sucesso
    for (int i=0; i<L; i++){
        char str[10];
        int tmp_cp, tmp_cc, tmp_time, tmp_cost, tmp_first, tmp_last, tmp_p, tmp_aut;

        if (fscanf(file_map, "%d %d %10s %d %d %d %d %d",
                   &tmp_cp,
                   &tmp_cc,
                   str,
                   &tmp_time,
                   &tmp_cost,
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
            time[i] = tmp_time;
            cost[i] = tmp_cost;
            first[i] = tmp_first;
            last[i] = tmp_last;
            period[i] = tmp_p;
        }

        else {
            printf("Data format error on line %d\n", i+2);
            free_vectors_map();
            fclose(file_map);
            return 0;
        }
        n_con++;
    }

    printf("Successfully read %d right connections from %d total!\n", n_con, L);
    fclose(file_map);
    return 0; 

}



// Funcao que abre e analisa o ficheiro .quests
int read_file_quests(char * filename_quests, int T){     
    FILE *file_quests = fopen(filename_quests, "r");
    if (!file_quests) {
        perror(filename_quests);
        exit(0);
    }
    printf("File opened successfully again!\n\n");

    char buffer[6]; // buffer para ler o nome da task
    
    // loop for que le o ficheiro linha a linha incrementando i até T
    for (int i=0; i<T; i++){
        // se ler 1 string e 3 inteiros sabemos que é task4, armazenamos e damos cast da funcao que a resolve
    
        fscanf(file_quests, "%6s ", buffer);

        if (strcmp(buffer, "Task4") == 0){
            (fscanf(file_quests, " %i %i %i ", &cidade1[i], &cidade2[i], &tempo_inicial[i]) == 3);
            printf ("%s", buffer);

            task[i] = 4;
            printf("Task 4\n");
            task4_func(i, tempo_inicial[i]);
        }
        else if (fscanf(file_quests, " %i %i ", &cidade1[i], &cidade2[i]) == 2){

            if (strcmp(buffer, "Task1") == 0)
            {            
                task[i] = 1;

                task1_func(i);
                printf("Task 1 selected\n");
            }  
            // task2
            else if (strcmp(buffer, "Task2") == 0){
                task[i] = 2;

               // printf("Task 2 selected\n");
                task2e3_func(i, time);
            }

            // task3
            else if (strcmp(buffer, "Task3") == 0){
                task[i] = 3;

              //  printf("Task 3 selected\n");
                task2e3_func(i, cost);
            }

            // task5
            else if (strcmp(buffer, "Task5") == 0){
                task[i] = 5;

                printf("Task 5 selected\n");
               // task5_func(i);
            }
            else {
            printf("Data format error on line %d\n", i+1);
            continue;
        }
            
        }
        
    }
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
    char token[5];
    
    // Lê token por token até ao fim do ficheiro
    while (fscanf(file_quests, "%5s", token) == 1) {

        // Se o token começa com "Task", conta uma nova task
        if (strncmp(token, "Task", 4) == 0) {
            num_tasks++;
        }
    }

    fclose(file_quests);
    printf("File contains %d tasks\n", num_tasks);
    return num_tasks;

}


#endif