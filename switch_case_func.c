#include <stdio.h>
#include <stdlib.h>

#include "header.h" // Para ter acesso às declarações

void function_case(FILE *file_clients, char *type_restriction, int *value_rest, char *transport_restriction, int *max_value_restriction, int i)
{

    if (fscanf(file_clients, " %c %i", type_restriction, value_rest) != 2)
        exit(0);
    switch (*type_restriction)
    {
    case 'A':

        switch (*value_rest)
        {

        case 1:
            if (fscanf(file_clients, "%10s", transport_restriction) == 1)
                *max_value_restriction = Enum_str_to_int(transport_restriction);
                else exit(0);

            break;

        case 2:
            if (fscanf(file_clients, "%i", max_value_restriction) != 1)
                exit(0);

            break;

        case 3:
            if (fscanf(file_clients, "%i", max_value_restriction) != 1)
                exit(0);

            break;
        }
        break;

    case 'B':

        switch (*value_rest)
        {

        case 1:
            if (fscanf(file_clients, "%i", max_value_restriction) != 1)
            exit(0);

            break;

        case 2:
            if (fscanf(file_clients, "%i", max_value_restriction) != 1)
            exit(0);

            break;
        }

        break;

    default:
        printf("Data format error on line %d\n", i + 1);
        break;
    }
}