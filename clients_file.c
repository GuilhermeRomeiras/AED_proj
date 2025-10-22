#ifndef clients_file_c
#define clients_file_c

#include "header.h" // Para ter acesso às declarações

#include <stdio.h>
#include <stdlib.h>

int read_file_clients(FILE *file_clients, Cli* client, Restricoes *rest)

{      

      if(fscanf(file_clients, "%d %d %d %d %c %*s %d",
                    &client->id,
                   &client->cidade_origem ,
                   &client->cidade_destino,
                   &client->tempo_inicial,
                   &client->preferencia,
                   &client->num_restricoes)!=6) exit(0);

        client->cidade_origem -= 1;
        client->cidade_destino -= 1;

        switch (client->num_restricoes)
        {
        
        //se não houver restrições
        case 0:
        
            break;
     
        //se houver uma restrição
        case 1: 

            function_case(file_clients, rest);

            break;
        //se houver duas restrições
        case 2:

            function_case(file_clients, rest);
            function_case(file_clients, rest);
            
            break;

        default:
            break;
            
        }
    return 1;
}

#endif