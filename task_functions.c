#ifndef TASK_FUNCTIONS_C
#define TASK_FUNCTIONS_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void task2_func(int con_atual){
    result[con_atual] = -2;
    int a = -1, lower_time = 0, i = 0;

    if ((cidade1[con_atual] < 1 || cidade2[con_atual] < 1 || cidade1[con_atual] > N || cidade2[con_atual] > N)) 
        {
            result[con_atual] = -1;
            return;
        }

    while(i<L){

    if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){

    if (a < time[i]){
        printf("HELO2: %i \n", a);
        lower_time = a;
        result[con_atual] = lower_time;
        
        if (a==-1) result[con_atual] = time[i];
        }

        a = time[i];

        }

    i++;

    }
     printf("The smallest time %i between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);

}


//task3 implementação
void task3_func(int con_atual){
    result[con_atual] = -2;
    int a = -1, lower_cost = 0, i = 0;

    if ((cidade1[con_atual] < 1 || cidade2[con_atual] < 1 || cidade1[con_atual] > N || cidade2[con_atual] > N)) 
        {
            result[con_atual] = -1;
            return;
        }

    while(i<L){

    if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){

    if (a < cost[i]){
         printf("HELO3: %i\n", a);
        lower_cost = a;
        result[con_atual] = lower_cost;
        if (a==-1) result[con_atual] = cost[i];
        }

        a = cost [i];

        }

    i++;

    }
    printf("The smaller cost is %i between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);


}


//task4 implementação

//task5 implementação
    
    




#endif