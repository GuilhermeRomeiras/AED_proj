#ifndef DJYNSKI_C
#define DJYNSKI_C

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "header.h"

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct _item {
    int vertex;
    int priority;
    struct _item *from;
} Item;

typedef struct {
    Item *queue;
    int capacity;
    int n;
} PQ;

PQ *PQinit(int N);
void PQdec(PQ *pq, int vertex, int new_priority);
void PQinsert(PQ *pq, int vertex, int priority);
int PQempty(PQ *pq);
int PQdelmin(PQ *pq);
void PQfree(PQ *pq);
void reconstruct_path(int *st, int *st_lig, Cli *cliente, Sol *Solucao);
int path_size_calculate(int *st, Cli *cliente, Sol *Solucao);

#if 0

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

#else

int calcular_proxima_partida(int current_time, int first, int last, int period) {
    int day = current_time / 1440;
    int time_in_day = current_time % 1440;

    // Try to find the next departure in the current day
    if (time_in_day <= last) {
        // Calculate the first possible departure >= current_time
        int first_departure_today = day * 1440 + first;

        if (time_in_day <= first) {
            return first_departure_today;
        }

        // Calculate the offset from first departure
        int periods_since_first = (time_in_day - first + period - 1) / period; // ceil
        int next_departure_in_day = first + periods_since_first * period;

        if (next_departure_in_day <= last) {
            return day * 1440 + next_departure_in_day;
        }
    }

    // If no valid departure today, return the first departure of the next day
    return (day + 1) * 1440 + first;
}

#endif

void print_node(Node n) {
    //printf("    city_idx: %d\n", n.city_idx);
    //printf("      weight: %d\n", n.weight);
    //printf("arrival_time: %d\n", n.arrival_time);
    //printf("        cost: %d\n", n.cost);
    //printf("     visited: %d\n", n.visited);
    //printf("     n_edges: %d\n", n.n_edges);
    //printf("     lig_idx: %d\n", n.lig_id);
}

struct wargs {
    int arrival_time, first, last, period, time;
    int cost;
    int dcost;
};

int get_weight_time(void *wargs) {
    struct wargs *w = wargs;
    return w->time+calcular_proxima_partida(w->arrival_time, w->first, w->last, w->period);
}

int get_weight_cost(void *wargs) {
    struct wargs *w = wargs;
    return w->cost+w->dcost;
}

int sortq(const void *node1, const void *node2) {
    Node n1 = **(Node**)node1;
    Node n2 = **(Node**)node2;

    return n1.weight - n2.weight;
}

int dijkstra(const adj *cidades, Cli client, Sol *Solucao, int N, const int *first, const int *last, const int *periods,
              const int *times, const int *costs, const int *automoveis, int (get_weight)(void*), Node **nodes, Restricoes rest)
{
    // TODO: check origin and destination for invalid values

    int q_capacity = 1;
    int n = 0;

    for (int i = 0; i < N; i++) {
        (*nodes)[i].cost = INT_MAX;
        (*nodes)[i].weight = INT_MAX;
        (*nodes)[i].arrival_time = INT_MAX;
    }

    Node **q = calloc(q_capacity, sizeof(*q));
    if (!q) {
        return -1;
    }
    
    (*nodes)[client.cidade_origem] = (Node){0};
    (*nodes)[client.cidade_origem].city_idx = client.cidade_origem;
    (*nodes)[client.cidade_origem].arrival_time = client.tempo_inicial;
    (*nodes)[client.cidade_origem].n_edges = 0;

    q[0] = *nodes+client.cidade_origem;
    n++;

    while(1) {
        if (n <= 0) {
            //printf("no mo items.. nigger\n");
            break;
        }

        //printf("============ Q ==========\n");
        for (int i = 0; i < n; i++) {
            //puts("");
            print_node(*q[i]);
        }
        //printf("========== END Q ==========\n");

        /* pop single item */
        Node *cur = q[0];
        cur->visited = 1;
        q[0] = q[n-1];
        n--;

        int delta_time = cur->arrival_time-client.tempo_inicial;

        if (delta_time > rest.max_tempo_total ||
            cur->cost > rest.max_custo_total) continue;

        //printf("checking city %d.. (%d items left in queue)\n", cur->city_idx, n);
        //printf("number of cons: %d\n", cidades[cur->city_idx].num_lig);

        if (cur->city_idx == client.cidade_destino) {
            //printf("got to destination!\n");
            free(q);
            return 0;
        }

        for (int i = 0; i < cidades[cur->city_idx].num_lig; i++) {
            //printf("con %d..\n", i);
            int city_idx = cidades[cur->city_idx].next_cidade[i];
            int lig_idx = cidades[cur->city_idx].lig_id[i];
            (*nodes)[city_idx].city_idx = city_idx;


            if ((*nodes)[city_idx].visited || automoveis[lig_idx] == rest.meio_proibido || costs[lig_idx] == rest.max_tempo_ligacao || times[lig_idx] == rest.max_tempo_ligacao) {
                //printf("already visited %d\n", city_idx);
                continue;
            }

            struct wargs wargs = {.arrival_time = cur->arrival_time, .time = times[lig_idx], .cost = cur->cost, .dcost = costs[lig_idx], .first = first[lig_idx], .last = last[lig_idx], .period = periods[lig_idx]};

            int new_weight = get_weight(&wargs);

            if ((*nodes)[city_idx].weight < new_weight) {
                Node *from = (*nodes)[city_idx].from;

                int from_idx = -1;
                if (from) from_idx = from->city_idx;

                //printf("city %d has a better con than %d to %d [%d] (%d vs %d)\n",
                        //city_idx,
                        //city_idx, cur->city_idx,
                        //from_idx, 
                       // (*nodes)[city_idx].weight, new_weight);
                continue;
            }

            (*nodes)[city_idx].cost = cur->cost+costs[lig_idx];
            int prox = calcular_proxima_partida(cur->arrival_time, first[lig_idx], last[lig_idx], periods[lig_idx]);
            (*nodes)[city_idx].arrival_time = times[lig_idx]+calcular_proxima_partida(cur->arrival_time, first[lig_idx], last[lig_idx], periods[lig_idx]);
            //printf("==== city %d ====\n", city_idx);
            //printf("arrived at %d\n", cur->arrival_time);
            //printf("next departure at %d\n", prox);
            (*nodes)[city_idx].weight = new_weight;
            (*nodes)[city_idx].n_edges = cur->n_edges+1;
            (*nodes)[city_idx].from  = cur;
            (*nodes)[city_idx].lig_id = lig_idx;

            //puts("");

            if (n >= q_capacity) {
                q_capacity *= 2;
                q = realloc(q, q_capacity*sizeof(*q));
                if (!q) {
                    perror("realloc()");
                    return -1;
                }
                //printf("reallocated nig\n");
            }
            //printf("writing to %d (capacity %d)\n", n, q_capacity);
            q[n] = *nodes+city_idx;
            n++;
        }

        qsort(q, n, sizeof(*q), &sortq);

    }

    for (int i = 0; i < N; i++) {
        //puts("");
        print_node((*nodes)[i]);
    }

    //printf("\nsolution:\n");
    for (Node *n = *nodes+client.cidade_destino; n; n = n->from) {
        //puts("");
        print_node(*n);
    }

    free(q);
    return -1;
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
    pq->capacity = N;
    pq->n = 0;
    return pq;
}

void PQfree(PQ *pq)
{
    free(pq->queue);
    free(pq);
}

BOOL PQempty(PQ *pq)
{
    return pq->n == 0 ? TRUE : FALSE;
}

void PQinsert(PQ *pq, int vertex, int priority)
{
    pq->queue[pq->n].vertex = vertex;
    pq->queue[pq->n].priority = priority;
    pq->n++;
}

int PQdelmin(PQ *pq)
{
    int i, min_idx = 0;

    for (i = 1; i < pq->n; i++)
    {
        if (pq->queue[i].priority < pq->queue[min_idx].priority)
            min_idx = i;
    }

    int min_vertex = pq->queue[min_idx].vertex;
    pq->queue[min_idx] = pq->queue[pq->n - 1];
    pq->n--;

    return min_vertex;
}

void PQdec(PQ *pq, int vertex, int new_priority)
{
    for (int i = 0; i < pq->n; i++)
    {
        if (pq->queue[i].vertex == vertex)
        {
            pq->queue[i].priority = new_priority;
            return;
        }
    }
}

#endif
