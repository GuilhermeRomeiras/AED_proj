#ifndef clients_file_c
#define clients_file_c

#include "header.h" // Para ter acesso às declarações
#include "global.h"

#include <stdio.h>
#include <stdlib.h>

int read_file_clients(FILE *file_clients)
{

    /*  typedef struct clients_file
   {  int queue;
      int I;

  } ;

  */
    int client = 0, total_clients = 0, cidade1 = 0, cidade2 = 0, tempo_inicial = 0, num_restrictions = 0;
    char string_torc[6], first_type_restriction, second_type_restriction, transport_restriction[10];
    int max_value_restriction1 = 0, max_value_restriction2 = 0;
    int first_value_rest = 0, sercond_value_rest = 0;

    if (fscanf(file_clients, "%d", &total_clients) != 1)
        exit(0); // ler o numero total de clients

    for (int i = 0; i < total_clients; i++)
    {
        if (fscanf(file_clients, "%d %d %d %d %5s %d", &client, &cidade1, &cidade2, &tempo_inicial, string_torc, &num_restrictions) != 6)
            exit(0);
        printf("restrição do client %i é %i \n", client, num_restrictions);

        switch (num_restrictions)
        {
        
        //se não houver restrições
        case 0:

            break;
        
        //se houver uma restrição
        case 1: function_case;
            printf("nesta task apenas há uma restrição \n");
           
        
        //se houver duas restrições
        case 2:

            if (fscanf(file_clients, "%c %i ", second_type_restriction, &max_value_restriction2) != 4)
                exit(0);
            
            break;

        

        default:
            printf("1Data format error on line %d\n", i + 1);
            break;
        }
    }
    return 1;
}

#endif