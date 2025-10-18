#ifndef DJYNSKI_C
#define DJYNSKI_C

#include <stdio.h>
#include <limits.h>

#include <header.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

// PQ com tabela não ordenada
typedef struct
{
    int vertex;
    double priority;
} Item;

typedef struct
{
    Item *queue;
    int size;
    int n_elem;
} PQ;

Item p_item;

PQ *PQinit(int maxN);
void PQdec(PQ *pq, int vertex, double new_priority);
void PQinsert(PQ *pq, int vertex, double priority);
int PQempty(PQ *pq);
int PQdelmin(PQ *pq);
void PQfree(PQ *pq);

// Dijkstra adaptado às nossas estruturas
void dijkstra(adj *cidades, int source, int N, int *cidade_part, int *cidade_cheg,
              int *time, int *cost, int optimize_time, int *st_lig)
{
    int st[N];
    int wt[N];

    PQ *pq = PQinit(N + 1);

    // Inicialização
    for (int v = 1; v <= N; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
        PQinsert(pq, v, INT_MAX);
    }

    wt[source] = 0.0;
    PQdec(pq, source, 0.0);

    // Algoritmo principal
    while (!PQempty(pq))
    {
        int v = PQdelmin(pq);

        if (wt[v] != INT_MAX)
        {

            // Percorre as adjacências de v
            for (int i = 0; i < cidades[v].num_lig; i++)
            {
                int w = cidades[v].next_cidade[i];
                int lig_id = cidades[v].lig_id[i];

                // Escolhe peso: tempo ou custo
                double peso = optimize_time ? time[lig_id] : cost[lig_id];

                // Relaxação
                if (wt[w] > wt[v] + peso)
                {
                    wt[w] = wt[v] + peso;
                    PQdec(pq, w, wt[w]);
                    st[w] = v;
                    st_lig[w] = lig_id; // para sabermos o id das ligacoes e acedermos a memoria instantaneamente sem ter de fazer mais varrimentos
                }
            }
        }
    }

    PQfree(pq);
}

PQ *PQinit(int maxN)
{   
    PQ *pq = malloc(sizeof(PQ));
    if (pq == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memória para PQ.\n");
        exit(0);
    }

    pq->queue = (Item *) malloc(maxN * sizeof(Item));
    pq->size = maxN;
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

void PQinsert(PQ *pq, int vertex, double priority)
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

void PQdec(PQ *pq, int vertex, double new_priority)
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