#ifndef clients_file_c
#define clients_file_c

#include "header.h" // Para ter acesso às declarações

#include <stdio.h>
#include <stdlib.h>

int read_file_clients(FILE *file_clients, Cli* client, Restricoes *rest)

{      

      if(fscanf(file_clients, "%d %d %d %d %c %*s %d",
                    &client->id,
                   &client->cidade_origem,
                   &client->cidade_destino,
                   &client->tempo_inicial,
                   &client->preferencia,
                   &client->num_restricoes)!=6) exit(0);
        
        
        switch (client->num_restricoes)
        {
        
        //se não houver restrições
        case 0:
        
            break;
     
        //se houver uma restrição
        case 1: 
            printf("nesta task apenas há uma restrição \n");

            function_case(file_clients, rest, client->id);

            break;
        //se houver duas restrições
        case 2:
            printf("nesta task há duas restrições \n");

            function_case(file_clients, rest, client->id);
            
            function_case(file_clients, rest, client->id);
            
            break;

        default:
            printf("Data format error on line %d\n", client->id + 1);
            break;
            
        }
/*
     printf("Client: %d, Cidade1: %d, Cidade2: %d, Tempo Inicial: %d, String_torc: %s, Num_restrictions: %d\n\n",
             client->id, client->cidade_origem, client->cidade_destino, client->tempo_inicial, client->preferencia, client->num_restricoes);

            printf("Restricoes:\n"
           "  tem_A1 = %d\n"
           "  tem_A2 = %d\n"
           "  tem_A3 = %d\n"
           "  tem_B1 = %d\n"
           "  tem_B2 = %d\n"
           "  meio_proibido = %d\n"
           "  max_tempo_ligacao = %d\n"
           "  max_custo_ligacao = %d\n"
           "  max_tempo_total = %d\n"
           "  max_custo_total = %d\n", rest->tem_A1, rest->tem_A2, rest->tem_A3,
           rest->tem_B1, rest->tem_B2,
           rest->meio_proibido,
           rest->max_tempo_ligacao, rest->max_custo_ligacao,
           rest->max_tempo_total, rest->max_custo_total);
*/
    return 1;
}

#endif