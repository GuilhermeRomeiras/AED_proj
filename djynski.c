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
int calcular_tempo_total(Sol *Solucao, Cli *cliente, int *time, int *first, int *last, int *period, int dijkstra_id);
void reconstruct_path(int *st, int *st_lig, int source, int destination, Sol *Solucao);

// Dijkstra adaptado às nossas estruturas
void dijkstra(adj *cidades, Cli *cliente, Sol *Solucao, int N, int *first, int *last, int *period,
              int *time, int *cost)
{
       if (cliente->cidade_origem < 0||cliente->cidade_destino < 0) {
        Solucao->valida = 0;
        return;
    }

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

                // Relaxação
                if (time_cost == 1)
                {
                    if (wt[w] > wt[v] + cost[dijkstra_id])
                    {
                        
                        wt[w] = wt[v] + cost[dijkstra_id];

                        //  printf("wt_v: %i\n", wt[v]);
                        PQdec(pq, w, wt[w]);
                        st[w] = v;

                        st_lig[w] = cidades[v].lig_id[i]; // para sabermos o id das ligacoes e acedermos a memoria instantaneamente sem ter de fazer mais varrimentos
                    }
                }

                else
                {   
                    
                     
                    if (wt[w] > wt[v] + time[dijkstra_id])
                    {
                        int tempo_lig = calcular_tempo_total(Solucao, cliente, time, first, last, period, dijkstra_id);
                        wt[w] = wt[v] + tempo_lig;
                        Solucao->tempo_total += tempo_lig; 
                         printf("wt_v: %i\n", wt[v]);
                        PQdec(pq, w, wt[w]);
                        st[w] = v;
                        st_lig[w] = cidades[v].lig_id[i]; // para sabermos o id das ligacoes e acedermos a memoria instantaneamente sem ter de fazer mais varrimentos
                    }
                }
            }
        }
    }

    reconstruct_path(st, st_lig, cliente->cidade_origem, cliente->cidade_destino, Solucao);
    Solucao->tempo_total = 0;
    Solucao->custo_total = 0;

    // Guardar o custo/tempo total
    if (Solucao->valida == 1)
    {
        // Percorre o caminho e soma AMBOS tempo e custo

        for (int i = 0; i < Solucao->caminho_size; i++)
        {   Solucao->tempo_total += calcular_tempo_total (Solucao, cliente, time, first, last, period, i);
            int sol_id = Solucao->caminho_id[i];
            Solucao->custo_total += cost[sol_id];
        }
    }

    // Libertar memória
    PQfree(pq);
    free(st);
    free(wt);
    free(st_lig);
}
// fim dijkstra

// Função para reconstruir o caminho
void reconstruct_path(int *st, int *st_lig, int source, int destination, Sol *Solucao)
{

    int current = destination;

    // Verificar se existe caminho
    if (st[current] == -1 && current != source)
    {
        Solucao->valida = 0;
        Solucao->caminho_size = 0;
        Solucao->caminho = NULL;
        return;
    }

    // PASSO 1: Contar quantos passos tem o caminho
    int path_length = 0;
    int temp = current;
    while (temp != source)
    {
        path_length++;
        temp = st[temp];
    }

    if (path_length == 0)
    {
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
    for (int i = path_length - 1; i >= 0; i--)
    {
        Solucao->caminho_id[i] = st_lig[current];
        Solucao->caminho[i] = st[current];
        current = st[current];
    }

    Solucao->valida = 1;
}

// Função para calcular o tempo total da rota considerando periodicidades
int calcular_tempo_total(Sol *Solucao, Cli *cliente, int *time, int *first, int *last, int *period, int dijkstra_id)
{
    int found_con = 0;
    int tempo_atual = cliente->tempo_inicial; // Hora de partida do cliente
    int resultado_tempo = 0;
    // Iterar por cada ligação no caminho

    int sol_id = dijkstra_id; // ID da ligação atual
    // Começar com a primeira partida do dia
    int first_period = first[sol_id];

    // Avançar até encontrar uma partida >= tempo_atual
    while (first_period < tempo_atual)
    {   
        first_period += period[sol_id];

        // Se ultrapassou a última partida do dia, vai para o dia seguinte
        if (first_period > last[sol_id])
        {
            first_period = first[sol_id] + 1440;
        }

        // Calcular hora de chegada desta ligação
        int hora_chegada = first_period + time[sol_id];
        
            if (found_con == 0){
                resultado_tempo = hora_chegada;
                found_con=1;
            }
            if (hora_chegada < tempo_atual) {
                resultado_tempo = hora_chegada;
            }
    }
    return resultado_tempo;
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