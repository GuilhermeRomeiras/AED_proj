#include "header.h"  // Para ter acesso às declarações
#include "global.h"

#include <stdio.h>
#include <stdlib.h>

int read_file_clients(FILE *file_clients){
    int client=0, cidade1=0, cidade2=0, tempo_inicial=0, num_restrictions=0;
    char string [6], first_type_restriction[3], second_type_restriction[3]; 
    int max_value_restriction1=0, max_value_restriction2=0;

    while(1)   
    {
        if (fscanf(file_clients, "%d %d %d %d %5s %d", &client, &cidade1, &cidade2, &tempo_inicial, string, &num_restrictions) != 6)
            exit(0);    
        printf("%iac  ", num_restrictions);

        switch (num_restrictions)
        {
        case 0:

            break;

        case 1:
            
            if (fscanf(file_clients, " %s", first_type_restriction) == 1){
                
            }

            else if (fscanf(file_clients, " %s %i", first_type_restriction, &max_value_restriction1) != 2){
                    
             }

            break;

            // task2
        case 2:

            if (fscanf(file_clients, " %s %i %s %i ", first_type_restriction, &max_value_restriction1, second_type_restriction, &max_value_restriction2) != 4)
                exit(0);
            break;


        default:
            // printf("Data format error on line %d\n", i+1);
            return 0;
        }
    }
    return 1;
}