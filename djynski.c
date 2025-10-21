#ifndef DJYNSKI_C
#define DJYNSKI_C

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "header.h"

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct
{
    int vertex;
    int priority;
} Item;

typedef struct
{
    Item *queue;
    int size;
    int n_elem;
} PQ;

PQ *PQinit(int N);
void PQdec(PQ *pq, int vertex, int new_priority);
void PQinsert(PQ *pq, int vertex, int priority);
int PQempty(PQ *pq);
int PQdelmin(PQ *pq);
void PQfree(PQ *pq);
void reconstruct_path(int *st, int *st_lig, Cli *cliente, Sol *Solucao);
int path_size_calculate(int *st, Cli *cliente, Sol *Solucao);

// Calculate next available departure time from tempo_atual
int calcular_proxima_partida(int tempo_atual, int first, int last, int period)
{
    // If we can catch the first departure
    if (tempo_atual <= first) {
        return first;
    }
    
    // If we're past the last departure, go to next day
    if (tempo_atual > last) {
        return first + 1440;
    }
    
    // Find next departure within today's schedule
    int next_departure = first;
    while (next_departure < tempo_atual) {
        next_departure += period;
    }
    
    // If we went past last departure, go to next day
    if (next_departure > last) {
        return first + 1440;
    }
    
    return next_departure;
}

void dijkstra(adj *cidades, Cli *cliente, Sol *Solucao, int N, int *first, int *last, int *period,
              int *time, int *cost)
{
    // Initialize Solucao to safe defaults
    Solucao->valida = 0;
    Solucao->caminho_size = 0;
    Solucao->tempo_total = 0;
    Solucao->custo_total = 0;
    Solucao->caminho = NULL;
    Solucao-> caminho_id = NULL;

    printf("N:%i Co:%i cd:%i \n", N, cliente->cidade_origem, cliente->cidade_destino);
    if (cliente->cidade_origem < 0 || cliente->cidade_destino < 0 || cliente->cidade_origem > N -1 || cliente->cidade_destino > N - 1) {
        return;
    }

    // Check if source equals destination
    if (cliente->cidade_origem == cliente->cidade_destino) {
        Solucao->valida = 0;
        Solucao->caminho_size = 0;
        return;
    }

    int time_cost = 0;
    
    if (cliente->preferencia == 'c') {
        time_cost = 1;  // Minimize cost
    }
    // Otherwise minimize time (time_cost = 0)

    int source = cliente->cidade_origem;
    int *st = malloc(N * sizeof(int));
    int *wt = malloc(N * sizeof(int));
    int *tempo_chegada = malloc(N * sizeof(int));  // Track actual arrival times
    int *st_lig = malloc(N * sizeof(int));


    PQ *pq = PQinit(N);

    // Initialization
    for (int v = 0; v < N; v++)
    {
        st[v] = -1;
        st_lig[v] = -1;  // Initialize to -1
        wt[v] = INT_MAX;
        tempo_chegada[v] = INT_MAX;
        PQinsert(pq, v, INT_MAX);
    }
    
    wt[source] = 0;
    tempo_chegada[source] = cliente->tempo_inicial;
    PQdec(pq, source, 0);
    
    // Main algorithm
    while (!PQempty(pq))
    {
        int v = PQdelmin(pq);

        if (v == cliente->cidade_destino)
        {
            break;
        }

        if (wt[v] != INT_MAX)
        {   
            // Iterate through adjacencies of v
            for (int i = 0; i < cidades[v].num_lig; i++)
            {
                int w = cidades[v].next_cidade[i];
                int dijkstra_id = cidades[v].lig_id[i];

                if (time_cost == 1)  // Minimize COST
                {
                    int custo_lig = cost[dijkstra_id];
                    
                    // For cost minimization, we still need to track time for scheduling
                    int partida = calcular_proxima_partida(tempo_chegada[v], 
                                                           first[dijkstra_id], 
                                                           last[dijkstra_id], 
                                                           period[dijkstra_id]);
                    int chegada = partida + time[dijkstra_id];
                    
                    if (wt[w] > wt[v] + custo_lig)
                    {
                        wt[w] = wt[v] + custo_lig;
                        tempo_chegada[w] = chegada;
                        PQdec(pq, w, wt[w]);
                        st[w] = v;
                        st_lig[w] = dijkstra_id;
                    }
                }
                else  // Minimize TIME
                {   
                    // Calculate next available departure from current city
                    int partida = calcular_proxima_partida(tempo_chegada[v], 
                                                           first[dijkstra_id], 
                                                           last[dijkstra_id], 
                                                           period[dijkstra_id]);
                    
                    // Calculate arrival time at destination city
                    int chegada = partida + time[dijkstra_id];
                    
                    // The "time" in Dijkstra is the total time elapsed
                    int tempo_total = chegada - cliente->tempo_inicial;
                    
                    if (wt[w] > tempo_total)
                    {
                        wt[w] = tempo_total;
                        tempo_chegada[w] = chegada;
                        PQdec(pq, w, wt[w]);
                        st[w] = v;
                        st_lig[w] = dijkstra_id;
                    }
                }
            }
        }
    }

    // Reconstruct path
    int path_length =path_size_calculate(st, cliente, Solucao);
    Solucao->caminho_size = path_length;
    Solucao->caminho = (int *)malloc(path_length * sizeof(int));
    Solucao->caminho_id = (int *)malloc(path_length * sizeof(int));
    reconstruct_path(st, st_lig, cliente, Solucao);

    // Calculate actual time and cost totals
    if (Solucao->valida == 1 && Solucao->caminho_size > 0)
    {
        int tempo_atual = cliente->tempo_inicial;
        
        for (int i = 0; i < Solucao->caminho_size; i++)
        {   
            int sol_id = Solucao->caminho_id[i];
            
            // Calculate when we can depart on this connection
            int partida = calcular_proxima_partida(tempo_atual, 
                                                   first[sol_id], 
                                                   last[sol_id], 
                                                   period[sol_id]);
            
            // Calculate arrival time
            int chegada = partida + time[sol_id];
            
            // Update current time for next connection
            tempo_atual = chegada;
            
            // Add cost
            Solucao->custo_total += cost[sol_id];
        }
        
        // Total time is from start to final arrival
        Solucao->tempo_total = tempo_atual - cliente->tempo_inicial;
    }

    // Free memory
    PQfree(pq);
    free(st);
    free(wt);
    free(tempo_chegada);
    free(st_lig);
}

void reconstruct_path(int *st, int *st_lig, Cli *cliente, Sol *Solucao){

    if (!Solucao->caminho || !Solucao->caminho_id) {
            Solucao->valida = 0;
            Solucao->caminho_size = 0;
    return;
    }
    
    int current = cliente->cidade_destino;

        // Build path arrays backwards
        // We need to store intermediate cities (not source, not destination)
        // and the connection IDs used
    for (int i = Solucao->caminho_size - 1; i >= 0; i--){

        if (st_lig[current] == -1 || st[current] == -1) {
            Solucao->valida = 0;
            Solucao->caminho_size = 0;
            return;
        }
            
        // Store the connection ID used to reach 'current'
        Solucao->caminho_id[i] = st_lig[current];
        printf("stlig:%i\n", st_lig[current]);
        // Store the previous city (intermediate city in path)
        Solucao->caminho[i] = st[current];
            
        // Move to previous city
        current = st[current];
        }

    Solucao->valida = 1;

}

int path_size_calculate(int *st, Cli *cliente, Sol *Solucao){

    int current = cliente->cidade_destino;
    int source = cliente->cidade_origem;
    
    // Check if path exists
    if (st[current] == -1 && current != source){
        Solucao->valida = 0;
        Solucao->caminho_size = 0;
        return 0;
    }

    // Count path length (number of edges/connections)
    int path_length = 0;
    int temp = current;
    while (temp != source && st[temp] != -1){
        path_length++;
        temp = st[temp];
        
        // Prevent infinite loop
        if (path_length > 10000) {
            Solucao->valida = 0;
            Solucao->caminho_size = 0;
            return 0;
        }
    }

    if (path_length == 0){
        Solucao->valida = 0;
        Solucao->caminho_size = 0;
        return 0;
    }

    return path_length;

}

PQ *PQinit(int N)
{
    PQ *pq = malloc(sizeof(PQ));
    if (!pq)
    {
        exit(0);
    }
    pq->queue = malloc(N * sizeof(Item));
    if (!pq->queue)
    {
        free(pq);
        exit(0);
    }
    pq->size = N;
    pq->n_elem = 0;
    return pq;
}

void PQfree(PQ *pq)
{
    free(pq->queue);
    free(pq);
}

BOOL PQempty(PQ *pq)
{
    return pq->n_elem == 0 ? TRUE : FALSE;
}

void PQinsert(PQ *pq, int vertex, int priority)
{
    pq->queue[pq->n_elem].vertex = vertex;
    pq->queue[pq->n_elem].priority = priority;
    pq->n_elem++;
}

int PQdelmin(PQ *pq)
{
    int i, min_idx = 0;

    for (i = 1; i < pq->n_elem; i++)
    {
        if (pq->queue[i].priority < pq->queue[min_idx].priority)
            min_idx = i;
    }

    int min_vertex = pq->queue[min_idx].vertex;
    pq->queue[min_idx] = pq->queue[pq->n_elem - 1];
    pq->n_elem--;

    return min_vertex;
}

void PQdec(PQ *pq, int vertex, int new_priority)
{
    for (int i = 0; i < pq->n_elem; i++)
    {
        if (pq->queue[i].vertex == vertex)
        {
            pq->queue[i].priority = new_priority;
            return;
        }
    }
}

#endif