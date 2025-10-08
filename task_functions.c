#ifndef TASK_FUNCTIONS_C
#define TASK_FUNCTIONS_C
#include <stdio.h>
#include <stdlib.h>


#include "header.h"  // Para ter acesso às declarações
#include "global.h"

//task1 implementação
void task1_func(int con_atual, int N, int L,  int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result){

    for (int i = 0; i<L; i++) {  
        if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){   
            result[con_atual] += 1;
        }
        else if ((cidade1[con_atual] < 1 || cidade2[con_atual] < 1 || cidade1[con_atual] > N || cidade2[con_atual] > N)) 
        {
            result[con_atual] = -1;
        }
    }

    //printf("There is %i direct connections between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);

}


//task2 implementação
//task3 implementação
void task2e3_func(int con_atual, int * compare, int N, int L, int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result){

    int found_con = 0, lower_compare = 0, i = 0;

    if ((cidade1[con_atual] < 1 || cidade2[con_atual] < 1 || cidade1[con_atual] > N || cidade2[con_atual] > N)) 
        {
            result[con_atual] = -1;
            return;
        }
     else if (cidade1[con_atual] == cidade2[con_atual]){
        result[con_atual] = 0;
        return;
    }
        
    while(i<L){
    if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){
        if (found_con==0)
        {
            lower_compare = compare[i];
        }
        
            found_con=1;

        if (lower_compare > compare[i]){
            lower_compare = compare[i];    
            
        }
    }
    i++;
    }
    result[con_atual] = -2;
    if (found_con == 1)
    result[con_atual] = lower_compare;
    //printf("The smaller compare is %i between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);


}


//task4 implementação
void task4_func(int con_atual, int hora_inicial, int N, int L, int *cidade1,  int *cidade2, int *cidade_part,  int *cidade_cheg,  int *result, int *time, int *first, int *last, int *period){

    int first_time = 0;
    int found_con = 0;
    int first_period = 0;

    if ((cidade1[con_atual] < 1 || cidade2[con_atual] < 1 || cidade1[con_atual] > N || cidade2[con_atual] > N || hora_inicial < 0 || hora_inicial >= 1440)){
        result[con_atual] = -1;
        return;
    }
    else if (cidade1[con_atual] == cidade2[con_atual]){
        result[con_atual] = hora_inicial;
        return;
    }

    result[con_atual] = -2;
    for (int i = 0; i<L; i++) {

        if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){  
            first_period = first[i];

            while (first_period < hora_inicial){
                first_period += period[i];

                if (first_period > last[i]){
                   first_period = first[i] + 1440;
                }
            }

            first_time = first_period + time [i];

            
            if (found_con == 0){
                result[con_atual] = first_time;
                found_con=1;
            }
            

            if (first_time < result[con_atual]) {
                result[con_atual] = first_time;
            }
        }
    
    }

}   

//task 5
void init_nodes(int N) {
    
    cidades = malloc((N+1) * sizeof(adj));
    for(int i = 1; i <= N; i++){        // Para cada cidade
        cidades[i].next_cidade = malloc(N_INICIAL * sizeof(int));  // Malloc individual
        cidades[i].lig_id = malloc(N_INICIAL * sizeof(int));       // Malloc individual
        cidades[i].num_lig = 0;
        cidades[i].capacidade = N_INICIAL;
    }

}

int nodes(int nc, int con_atual, int tmp_cp, int num_lig) {

    if(con_atual >= cidades[tmp_cp].capacidade){
        cidades[tmp_cp].next_cidade = realloc(cidades[tmp_cp].next_cidade, (cidades[tmp_cp].capacidade) * 2 * sizeof(int));
        cidades[tmp_cp].lig_id = realloc(cidades[tmp_cp].lig_id, (cidades[tmp_cp].capacidade) * 2 * sizeof(int));
        cidades[tmp_cp].capacidade = cidades[tmp_cp].capacidade * 2;
    }

    cidades[tmp_cp].next_cidade[num_lig] = nc;
    cidades[tmp_cp].lig_id[num_lig] = con_atual;
    cidades[tmp_cp].num_lig++;
    return 0;

}

void task5_func(int con_atual, int N, int *cidade1,  int *cidade2,  int *result) {
    

    int city1 = cidade1[con_atual];
    int city2 = cidade2[con_atual];

     // Verificar se é um problema admissível
    if (city1 < 1 || city2 < 1 || city1 > N || city2 > N || city1 == city2) {
        result[con_atual] = -1;
        return;
    }
    
    // Verificar se há conexão direta (adjacências de city1)
    for (int i = 0; i < cidades[city1].num_lig; i++) {
        if (cidades[city1].next_cidade[i] == city2) {
            result[con_atual] = 0; 
            return;
        }
    }
    
    // Se não há conexão direta, procurar cidade intermediária para cada vizinho de city1
    for (int i = 0; i < cidades[city1].num_lig; i++) {
        int cidade_intermediaria = cidades[city1].next_cidade[i];
        
        // Verificar se cidade intermediária conecta a city2
        for (int j = 0; j < cidades[cidade_intermediaria].num_lig; j++) {
            if (cidades[cidade_intermediaria].next_cidade[j] == city2) {
                result[con_atual] = 1;
                return;
            }
        }
    }
    
}




#endif
