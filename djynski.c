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
void reconstruct_path(int *st, int *st_lig, int source, int destination, Sol *Solucao);


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
    for (int v = 0; v < N; v++)
    {
        st[v] = -1;
        wt[v] = INT_MAX;
        PQinsert(pq, v, INT_MAX);
    }

    wt[source] = 0;
    PQdec(pq, source, 0);
    // Algoritmo principal

    while (!PQempty(pq))
    {   
        int v = PQdelmin(pq);
        
        if (v == cliente->cidade_destino)
        {
            break;
        }
        

        if (wt[v] != INT_MAX)
        {

            // Percorre as adjacências de v
            for (int i = 0; i < cidades[v].num_lig; i++)
            {
                // printf("%i : %i\n", j++, PQempty(pq));
                int w = cidades[v].next_cidade[i];
                int dijkstra_id = cidades[v].lig_id[i];

                // Escolhe peso: tempo ou custo
                int peso = time_cost ? time[dijkstra_id] : cost[dijkstra_id];

                
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

    reconstruct_path(st, st_lig, cliente->cidade_origem, cliente->cidade_destino, Solucao);
    Solucao->custo_total=0;
    Solucao->tempo_total =0;
    // Guardar o custo/tempo total
    if (Solucao->valida == 1) {

        int dest = cliente->cidade_destino;
        if (cliente->preferencia == 'c') {
            Solucao->custo_total = wt[dest];
        }     
        else {
            Solucao->tempo_total = wt[dest];
        }
    }
    
    // Libertar memória
    PQfree(pq);
    free(st);
    free(wt);
    free(st_lig);

}


// Função para reconstruir o caminho
void reconstruct_path(int *st, int *st_lig, int source, int destination, Sol *Solucao) {
    
    int current = destination;  
    
    // Verificar se existe caminho
    if (st[current] == -1 && current != source) {
        Solucao->valida = 0;
        Solucao->caminho_size = 0;
        Solucao->caminho = NULL;
        return;
    }
    
    // PASSO 1: Contar quantos passos tem o caminho
    int path_length = 0;
    int temp = current;
    while (temp != source) {
        path_length++;
        temp = st[temp];
    }
    
    if(path_length == 0) {
        Solucao->valida = 0;
        Solucao->caminho_size = 0;
        return;
    }

    Solucao->caminho = (int *)malloc(path_length * sizeof(int));
    Solucao->caminho_id = (int *)malloc(path_length * sizeof(int));
    Solucao->caminho_size = path_length;
    current = destination;  
    
    // PASSO 3: Preencher de trás para a frente, já invertendo!
    // Começamos a preencher do fim do array (posição path_length-1)
    // e vamos recuando até à posição 0    
    for (int i = path_length - 1; i >= 0; i--) {
        Solucao->caminho_id[i] = st_lig[current];
        Solucao->caminho[i] = st[current];
        current = st[current];
    }
    
    Solucao->valida = 1;
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