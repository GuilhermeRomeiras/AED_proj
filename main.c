#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "header.h"

int main(int argc, char *argv[])
{
    int N = 0, L = 0;

    // verificar os comandos do terminal
    if (argc != 3)
    {
        // fprintf(stderr, "argument count is wrong\n");
        exit(0);
    }

    char *filename_map = argv[1];
    char *filename_clients = argv[2];

    // pointer para o ficheiro a ser aberto
    FILE *file_map = fopen(filename_map, "r");

    if (!file_map)
    {   
        perror(filename_map);
        exit(0);
    }

    FILE *file_clients = fopen(filename_clients, "r");
    if (!file_clients)
    {   
        fclose(file_map);
        perror(filename_clients);
        exit(0);
    }
    char *results_filename = create_results_filename(filename_clients);

     FILE* ptr_results_file = fopen(results_filename, "w");
     if (!ptr_results_file)
     {
         perror(results_filename);
         exit(0);
     }

    // printf("File opened successfully!\n");

    // o fscanf para extrair o cabecalho
    if (fscanf(file_map, "%d %d", &N, &L) != 2)
    {
        // printf("Header error\n");
        fclose(file_clients);
        fclose(file_map);
        exit(0);
    }

    // armazenamento dinamico dos arrays map
    int *cidade_part = malloc(L * sizeof(int)); // coluna 1
    int *cidade_cheg = malloc(L * sizeof(int)); // coluna 2
    int *automovel = malloc(L * sizeof(int));   // coluna 3 (enum)
    int *time = malloc(L * sizeof(int));        // coluna 5
    int *cost = malloc(L * sizeof(int));        // coluna 4
    int *first = malloc(L * sizeof(int));       // coluna 6
    int *last = malloc(L * sizeof(int));        // coluna 7
    int *period = malloc(L * sizeof(int));      // coluna 8

    if (cidade_part == NULL || cidade_cheg == NULL || automovel == NULL ||
    time == NULL || cost == NULL || first == NULL || last == NULL || period == NULL)
    {
        exit(0);
    }

    adj *p_cidades = malloc((N+1) * sizeof(adj));
    if (p_cidades == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memória para p_cidades.\n");
        exit(0);
    }

    Cli        p_clients_file = {0};
    Restricoes         p_rest = {0};
    Sol                 p_sol = {0};

    read_file_map(file_map, N, L,
                  cidade_part, cidade_cheg, automovel, time, cost, first, last, period, p_cidades);

    // print_arrays();

    //print_city(N, p_cidades);


    int total_clients;
    if (fscanf(file_clients, "%d", &total_clients) != 1)
        {
            exit(0);
        }

    for (int i = 1; i <= total_clients; i++)
    {  

        p_rest.max_custo_ligacao = INT_MAX;
        p_rest.max_custo_total   = INT_MAX;
        p_rest.max_tempo_ligacao = INT_MAX;
        p_rest.max_tempo_total   = INT_MAX;
        p_rest.meio_proibido     = INT_MAX;

        read_file_clients(file_clients, &p_clients_file, &p_rest);

        int err = 0;
        Node *nodes = NULL;

        if (p_clients_file.cidade_origem >= 0 && p_clients_file.cidade_destino >= 0 && p_clients_file.cidade_origem < N && p_clients_file.cidade_destino < N) {

            nodes = calloc(N, sizeof(*nodes));
            if (!nodes) {
                // TODO: free everything
                return -1;
            }

            if (p_clients_file.preferencia == 'c')
                err = dijkstra(p_cidades, p_clients_file, &p_sol, N, first, last, period, time, cost, automovel, &get_weight_cost, &nodes, p_rest);

            else if (p_clients_file.preferencia == 't')
                err = dijkstra(p_cidades, p_clients_file, &p_sol, N, first, last, period, time, cost, automovel, &get_weight_time, &nodes, p_rest);

        } else err = 1;

        printf("dijkstra returned %d\n", err);

        /*
           printf("Client: %d, Cidade1: %d, Cidade2: %d, Tempo Inicial: %d, String_torc: %c, Num_restrictions: %d\n\n",
           p_clients_file->id, p_clients_file->cidade_origem, p_clients_file->cidade_destino, p_clients_file->tempo_inicial, p_clients_file->preferencia, p_clients_file->num_restricoes);

           printf("Restricoes:\n"
           "  meio_proibido = %d\n"
           "  max_tempo_ligacao = %d\n"
           "  max_custo_ligacao = %d\n"
           "  max_tempo_total = %d\n"
           "  max_custo_total = %d\n",
           p_rest->meio_proibido,
           p_rest->max_tempo_ligacao, p_rest->max_custo_ligacao,
           p_rest->max_tempo_total, p_rest->max_custo_total);*/


        Node *solution = NULL;
        int n_nodes = 0;
        if (!err) {
            n_nodes = nodes[p_clients_file.cidade_destino].n_edges+1;
            printf("getting solution.. (%d nodes)\n", n_nodes);
            solution = malloc(n_nodes*sizeof(*solution));
            if (!solution) {
                // TODO: free
                perror("malloc()");
                return -1;
            }

            Node *cur = nodes+p_clients_file.cidade_destino;
            for (int i = n_nodes-1; i >= 0; i--) {
                solution[i] = *cur;
                cur = cur->from;
            }

            for (int i = 0; i < n_nodes; i++) {
                print_node(solution[i]);
            }
        }

        print_results(ptr_results_file, solution, n_nodes, automovel, p_clients_file);

        free(solution);
        free(nodes);
        free(p_sol.caminho_id);
        free(p_sol.caminho);

    }

    fclose(file_clients);

    // close results file
   fclose(ptr_results_file);

    free(results_filename);
    

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors_map(cidade_part, cidade_cheg, automovel, time, cost, first, last, period);

    //  free_vectors_quests(task, cidade1, cidade2, tempo_inicial, result);
    free_cidades(N, p_cidades);
    // free(results_filename);

    return 0;
}
