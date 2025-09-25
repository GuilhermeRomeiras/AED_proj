#ifndef TASK_FUNCTIONS_C
#define TASK_FUNCTIONS_C
#include <stdio.h>



#include "header.h"  // Para ter acesso às declarações
#include "global.h"

//task1 implementação
void task1_func(int con_atual){

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
void task2e3_func(int con_atual, int * compare){

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
void task4_func(int con_atual, int hora_inicial){

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


//task5 implementação
void task5_func(int con_atual) {

    int city_a = cidade1[con_atual];
    int city_b = cidade2[con_atual];

    // Verificar se é um problema admissível
    if (city_a < 1 || city_b < 1 || city_a > N || city_b > N || cidade1[con_atual] == cidade2[con_atual]) {
        result[con_atual] = -1;
        return;
    }

    // Verificar se NÃO existe ligação direta (pré-requisito da task5)
    for (int i = 0; i < L; i++) {
        if ((cidade_part[i] == city_a && cidade_cheg[i] == city_b) ||
            (cidade_part[i] == city_b && cidade_cheg[i] == city_a)) {
            result[con_atual] = -1;
            return;
        }
    }   

    // Procurar cidade intermediária
    for (int i = 0; i < L; i++) {
        int cidade_intermed = -1;
        
        // Ver se esta ligação conecta com city_a
        if (cidade_part[i] == city_a) {
            cidade_intermed = cidade_cheg[i];
        } 
        else if (cidade_cheg[i] == city_a) {
            cidade_intermed = cidade_part[i];
        }
        
        // Se encontrou intermediária, ver se ela conecta com city_b
        if (cidade_intermed != -1) {
            for (int j = 0; j < L; j++) {
                if ((cidade_part[j] == cidade_intermed && cidade_cheg[j] == city_b) ||
                    (cidade_cheg[j] == cidade_intermed && cidade_part[j] == city_b)) {
                    result[con_atual] = 1;  // Encontrou caminho
                    return;
                }
            }
        }
    }
    result[con_atual] = 0;  // Não encontrou caminho

}
    




#endif