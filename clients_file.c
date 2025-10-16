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
    char string_torc[6], type_restriction, transport_restriction[10];
    int max_value_restriction = 0, value_rest = 0;


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

        
            printf("Client: %d, Cidade1: %d, Cidade2: %d, Tempo Inicial: %d, String_torc: %s, Num_restrictions: %d\n\n",
             client, cidade1, cidade2, tempo_inicial, string_torc, num_restrictions);

            break;
        
        //se houver uma restrição
        case 1: 
            printf("nesta task apenas há uma restrição \n");

            function_case(file_clients, &type_restriction, &value_rest, transport_restriction, &max_value_restriction, i);

            printf("Client: %d, Cidade1: %d, Cidade2: %d, Tempo Inicial: %d, String_torc: %s, Num_restrictions: %d, type_restriction: %c%i, max_value_restriction: %i\n\n",
             client, cidade1, cidade2, tempo_inicial, string_torc, num_restrictions, type_restriction, value_rest, max_value_restriction);


           
            break;
        //se houver duas restrições
        case 2:
            printf("nesta task há duas restrições \n");

            function_case(file_clients, &type_restriction, &value_rest, transport_restriction, &max_value_restriction, i);
            
            printf("Client: %d, Cidade1: %d, Cidade2: %d, Tempo Inicial: %d, String_torc: %s, Num_restrictions: %d, type_restriction: %c%i, max_value_restriction: %i ",
             client, cidade1, cidade2, tempo_inicial, string_torc, num_restrictions, type_restriction, value_rest, max_value_restriction);

            function_case(file_clients, &type_restriction, &value_rest, transport_restriction, &max_value_restriction, i);
            
            printf("type_restriction: %c%i, max_value_restriction: %i\n\n", type_restriction, value_rest, max_value_restriction);

            
            break;

        default:
            printf("Data format error on line %d\n", i + 1);
            break;
        }

    }
    return 1;
}

#endif