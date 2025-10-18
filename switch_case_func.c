#include <stdio.h>
#include <stdlib.h>

#include "header.h" // Para ter acesso às declarações

void function_case(FILE *file_clients, Restricoes *rest, int client_id)
{
    char type_restriction;
    int value_rest;
    char transport_restriction[10];

    if (fscanf(file_clients, " %c %i", &type_restriction, &value_rest) != 2)
        exit(0);
    switch (type_restriction)
    {
    case 'A':

        switch (value_rest)
        {

        case 1:
            if (fscanf(file_clients, "%10s", transport_restriction) == 1){
                rest->meio_proibido = Enum_str_to_int(transport_restriction);
                rest->tem_A1 = 1;
            }

            break;

        case 2:
            if (fscanf(file_clients, "%i", &rest->max_tempo_ligacao) == 1){
                rest->tem_A2 = 1;
            }

            break;

        case 3:
            if (fscanf(file_clients, "%i", &rest->max_custo_ligacao) == 1){
                rest->tem_A3 = 1;
            }

            break;
        }
        break;

    case 'B':

        switch (value_rest)
        {

        case 1:
            if (fscanf(file_clients, "%i", &rest->max_tempo_total) == 1){
                rest->tem_B1 = 1;
            }
           

            break;

        case 2:
            if (fscanf(file_clients, "%i", &rest->max_custo_total) == 1){
                rest->tem_B2 = 1;
            }
           

            break;
        }

        break;

    default:
        printf("Data format error on line %d\n", client_id + 1);
        break;
    }
}
