#ifndef TASK_FUNCTIONS_C
#define TASK_FUNCTIONS_C
#include "header.h"


void task1_func(int con_atual){

    result[con_atual] = 0;

    for (int i = 0; i<L; i++) {  
        if ((cidade1[con_atual] == cidade_part[i] && cidade2[con_atual] == cidade_cheg[i]) || (cidade1[con_atual] == cidade_cheg[i] && cidade2[con_atual] == cidade_part[i])){   
            result[con_atual] += 1;
        }
    }
    printf("There is %i direct connections between %d and %d\n", result[con_atual], cidade1[con_atual], cidade2[con_atual]);

}
#endif