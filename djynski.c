#ifndef DJYNSKI_C
#define DJYNSKI_C

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "header.h"

typedef int BOOL;
#define TRUE 1
#define FALSE 0



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


int get_weight_time(void *wargs) {
    struct wargs *w = wargs;
    return w->time+calcular_proxima_partida(w->arrival_time, w->first, w->last, w->period);
}

int get_weight_cost(void *wargs) {
    struct wargs *w = wargs;
    return w->cost+w->dcost;
}

int find_min_q(Node **q, int n) {
    int min_idx = 0;
    for (int i = 0; i < n; i++) {
        min_idx = q[i]->weight < q[min_idx]->weight ? i : min_idx;
    }
    return min_idx;
}

int dijkstra(const adj *cidades, Cli client, int N, const int *first, const int *last, const int *periods,
              const int *times, const int *costs, const int *automoveis, int (get_weight)(void*), Node **nodes, Restricoes rest){

    int q_capacity = 1024;
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

    while(n>0) {

        // retirar da PQ o com maior prioridade
        int min_idx = find_min_q(q, n);
        Node *cur = q[min_idx];
        cur->visited = 1;
        q[min_idx] = q[n-1];
        n--;

        int delta_time = cur->arrival_time-client.tempo_inicial;

        if (delta_time > rest.max_tempo_total ||
            cur->cost > rest.max_custo_total) continue;


        if (cur->city_idx == client.cidade_destino) {
            free(q);
            return 0;
        }

        for (int i = 0; i < cidades[cur->city_idx].num_lig; i++) {
            int city_idx = cidades[cur->city_idx].next_cidade[i];
            int lig_idx = cidades[cur->city_idx].lig_id[i];
            (*nodes)[city_idx].city_idx = city_idx;


            if ((*nodes)[city_idx].visited || automoveis[lig_idx] == rest.meio_proibido || costs[lig_idx] > rest.max_custo_ligacao || times[lig_idx] > rest.max_tempo_ligacao) {
                continue;
            }

            struct wargs wargs = {.arrival_time = cur->arrival_time, .time = times[lig_idx], .cost = cur->cost, .dcost = costs[lig_idx], .first = first[lig_idx], .last = last[lig_idx], .period = periods[lig_idx]};

            int new_weight = get_weight(&wargs);

            if ((*nodes)[city_idx].weight < new_weight) continue;

            (*nodes)[city_idx].cost = cur->cost+costs[lig_idx];
            (*nodes)[city_idx].arrival_time = times[lig_idx]+calcular_proxima_partida(cur->arrival_time, first[lig_idx], last[lig_idx], periods[lig_idx]);
            (*nodes)[city_idx].weight = new_weight;
            (*nodes)[city_idx].n_edges = cur->n_edges+1;
            (*nodes)[city_idx].from  = cur;
            (*nodes)[city_idx].lig_id = lig_idx;


            if (n >= q_capacity) {
                q_capacity *= 2;
                q = realloc(q, q_capacity*sizeof(*q));
                if (!q) {
                    perror("realloc()");
                    return -1;
                }
            }
            q[n] = *nodes+city_idx;
            n++;
        }

    }

    free(q);
    return -1;
}


#endif
