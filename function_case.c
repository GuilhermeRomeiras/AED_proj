

void function_case(void)
{

    if (fscanf(file_clients, " %c %i", first_type_restriction, &first_value_rest) != 1)
        exit(0);
    switch (first_type_restriction)
    {
    case 'A':

        switch (first_value_rest)
        {

        case 1:
            printf("cheguei ao A1 \n");
            if (fscanf(file_clients, "%10s", transport_restriction) != 1)
                exit(0);

            break;

        case 2:
            printf("cheguei ao A2 \n");
            if (fscanf(file_clients, "%i", &max_value_restriction1) != 1)
                exit(0);

            break;

        case 3:
            printf("cheguei ao A3 \n");
            if (fscanf(file_clients, "%i", &max_value_restriction1) != 1)
                exit(0);

            break;
        }
        break;

    case 'B':

        switch (first_value_rest)
        {
            if (fscanf(file_clients, "%i", &max_value_restriction1) != 1)
                exit(0);

        case 1:
            printf("cheguei ao B1 \n");

            break;

        case 2:
            printf("chguei ao B2 \n");

            break;
        }

        break;

    default:
        printf("Data format error on line %d\n", i + 1);
        break;
    }
}