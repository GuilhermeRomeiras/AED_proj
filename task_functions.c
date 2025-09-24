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

    printf("There is %i direct connections between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);

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
    printf("The smaller compare is %i between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);


}


//task4 implementação
void task4_func(int con_atual, int hora_inicial){
    int first_time = 0;
    int found_con = 0;
    result[con_atual] = -2;
    int first_period = 0;

    for (int i = 0; i<L; i++) {  
        
        if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){  
            first_period = first[i];

            for (; first_period < hora_inicial; first_period += period[i]);         
            
             first_time = first_period + time [i];

            
            if (found_con == 0){
                result[con_atual] = first_time;
            }   

            found_con = 1;

            if (first_time < result[con_atual]) {
                 result[con_atual] = first_time;
            }

        }
        else if ((cidade1[con_atual] < 1 || cidade2[con_atual] < 1 || cidade1[con_atual] > N || cidade2[con_atual] > N)) 
        {
            result[con_atual] = -1;
        }
    }

    printf("There best time is %i between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);

}
//task5 implementação
    
    




#endif