#ifndef DJYNSKI_C
#define DJYNSKI_C

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "header.h"

typedef int BOOL;
#define TRUE 1
#define FALSE 0

// PQ com tabela não ordenada
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

// Dijkstra adaptado às nossas estruturas
void dijkstra(adj *cidades, Cli *cliente, Sol *Solucao, int N,
              int *time, int *cost)
{
    int time_cost = 0;

    switch (cliente->preferencia)
    {
    case 'c':
        time_cost = 1;
        break;
    }

    int source = cliente->cidade_origem;
    int *st = malloc((N) * sizeof(int));
    int *wt = malloc((N) * sizeof(int));
    int *st_lig = malloc((N) * sizeof(int));

    PQ *pq = PQinit(N);

    // Inicialização
    for (int v = 1; v <= N; v++)
    {
        st[v - 1] = -1;
        wt[v - 1] = INT_MAX;
        PQinsert(pq, v, INT_MAX);
    }

    wt[source - 1] = 0;
    PQdec(pq, source, 0);
    // Algoritmo principal

    while (!PQempty(pq))
    {
        int v = PQdelmin(pq) - 1;
        
        if (v == cliente->cidade_destino)
            break;

        if (wt[v] != INT_MAX)
        {
            printf("%i \n", wt[v]);

            // Percorre as adjacências de v
            for (int i = 0; i < cidades[v].num_lig; i++)
            {
                // printf("%i : %i\n", j++, PQempty(pq));
                int w = cidades[v].next_cidade[i];
                int lig_id = cidades[v].lig_id[i];

                // Escolhe peso: tempo ou custo
                int peso = time_cost ? time[lig_id] : cost[lig_id];

                // printf("client: %i\n %i : %i\n", cliente->id, i, st[v]);

                // Relaxação
                if (wt[w] > wt[v] + peso)
                {
                    wt[w] = wt[v] + peso;

                    //  printf("wt_v: %i\n", wt[v]);
                    PQdec(pq, w, wt[w]);
                    st[w] = v;
                    st_lig[w] = cidades[v].lig_id[i]; // para sabermos o id das ligacoes e acedermos a memoria instantaneamente sem ter de fazer mais varrimentos
                }
            }
        }
    }

    PQfree(pq);
    free(st);
    free(wt);
    free(st_lig);
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

    // Procura o mínimo
    for (i = 1; i < pq->n_elem; i++)
    {
        if (pq->queue[i].priority < pq->queue[min_idx].priority)
            min_idx = i;
    }

    // Guarda o vértice com prioridade mínima
    int min_vertex = pq->queue[min_idx].vertex;

    // Move o último para a posição do mínimo
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