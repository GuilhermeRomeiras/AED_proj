#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "global.h"

void init_nodes(int N) {
    
    cidades = malloc((N+1) * sizeof(adj));
    for(int i = 1; i <= N; i++){        // Para cada cidade
        cidades[i].next_cidade = malloc(N_INICIAL * sizeof(int));  // Malloc individual
        cidades[i].lig_id = malloc(N_INICIAL * sizeof(int));       // Malloc individual
        cidades[i].num_lig = 0;
        cidades[i].capacidade = N_INICIAL;
    }

}

int nodes(int ntmp_cp, int ntmp_cc, int con_atual) {

    if( cidades[ntmp_cp].num_lig >= cidades[ntmp_cp].capacidade){
        cidades[ntmp_cp].next_cidade = realloc(cidades[ntmp_cp].next_cidade, (cidades[ntmp_cp].capacidade) * 2 * sizeof(int));
        cidades[ntmp_cp].lig_id = realloc(cidades[ntmp_cp].lig_id, (cidades[ntmp_cp].capacidade) * 2 * sizeof(int));
        cidades[ntmp_cp].capacidade = cidades[ntmp_cp].capacidade * 2;
    }

    if(cidades[ntmp_cc].num_lig >= cidades[ntmp_cc].capacidade){
        cidades[ntmp_cc].next_cidade = realloc(cidades[ntmp_cc].next_cidade, (cidades[ntmp_cc].capacidade) * 2 * sizeof(int));
        cidades[ntmp_cc].lig_id = realloc(cidades[ntmp_cc].lig_id, (cidades[ntmp_cc].capacidade) * 2 * sizeof(int));
        cidades[ntmp_cc].capacidade = cidades[ntmp_cc].capacidade * 2;
    }

    cidades[ntmp_cp].next_cidade[cidades[ntmp_cp].num_lig] = ntmp_cc;
    cidades[ntmp_cp].lig_id[cidades[ntmp_cp].num_lig] = con_atual;
    cidades[ntmp_cp].num_lig++;

    cidades[ntmp_cc].next_cidade[cidades[ntmp_cc].num_lig] = ntmp_cp;
    cidades[ntmp_cc].lig_id[cidades[ntmp_cc].num_lig] = con_atual;
    cidades[ntmp_cc].num_lig++;
    return 0;

}


// Funcao auxiliar para imprimir a rede de cidades
void print_city (int N) {
    printf("N: %i \n", N);
    printf("\n=== city Data ===\n");
   
    for (int i = 1; i <= N; i++) {
        printf("City %d:", i);
        for (int j = 0; j < cidades[i].num_lig; j++)
        {         
                 printf("  next city: %d  lig_id: %d\n",
                   cidades[i].next_cidade[j], cidades[i].lig_id[j]);
        }
        printf("\n");
        printf("  num_lig: %d\n", cidades[i].num_lig);
        printf(" capacidade: %d\n\n", cidades[i].capacidade);
    }
}

// Funcao auxiliar para imprimir os dados dos arrays
void print_arrays (int L, int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period) {

    printf("\n=== Array Data ===\n");
    for (int i = 0; i < L; i++) {
        const char *mode_str = Enum_int_to_str(automovel[i]);

        printf("Connection %d:\n", i+1);
        printf("  cidade_part: %d\n", cidade_part[i]);
        printf("  cidade_cheg: %d\n", cidade_cheg[i]);
        printf("  automovel: %s (%d)\n", mode_str, automovel[i]);
        printf("  time: %d\n", time[i]);
        printf("  cost: %d\n", cost[i]);
        printf("  first: %d\n", first[i]);
        printf("  last: %d\n", last[i]);
        printf("  period: %d\n\n", period[i]);
    }

}


// Funcao que transforma a string do ficheiro em inteiro para melhor manipulacao
int Enum_str_to_int(const char *str){
    
    if (strcmp(str, "aviao") == 0) return AVIAO;
    else if (strcmp(str, "comboio") == 0) return COMBOIO;
    else if (strcmp(str, "barco") == 0) return BARCO;
    else if (strcmp(str, "autocarro") == 0) return AUTOCARRO;
    else {
        //printf("Invalid transportation in connection %d\n", num_con_err+1);
        return 0; // Retorna 0 para transporte invalido
    }

}


// Funcao inversa que transforma o inteiro de volta para string para dar print ou escrever no ficheiro de saida. O parametro transport_enum Ã© extraido,
// quando necessario, do valor automovel(i) que se queira escrever fazendo transport_enum = automovel(i) e de seguida chamando esta funcao
const char* Enum_int_to_str(int transport_enum){ 

    switch(transport_enum) {
        case AVIAO:     return "aviao";
        case COMBOIO:   return "comboio";
        case BARCO:     return "barco";
        case AUTOCARRO: return "autocarro";
        default:        return "incorrect transport";
    }

}



// free dos dados armazenados do ficheiro map
void free_vectors_map(int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period) {

    free(cidade_part);
        cidade_part = NULL;

    free(cidade_cheg); 
        cidade_cheg = NULL; 

    free(automovel);
       automovel = NULL; 
       
    free(time);
        time = NULL;   

    free(cost);
        cost = NULL;

    free(first);
       first = NULL;

    free(last);
        last = NULL; 

    free(period);
        period = NULL; 

}



// free dos dados armazenados do ficheiro quests
void free_vectors_quests(int *task, int *cidade1, int *cidade2, int *tempo_inicial, int *result) {

    free(task);
        task = NULL;

    free(cidade1); 
        cidade1 = NULL; 

    free(cidade2);
       cidade2 = NULL; 

    free(tempo_inicial);
        tempo_inicial = NULL; 
    free(result);
        result = NULL;

}

void free_cidades(int N) {

    for(int i = 1; i <= N; i++){        // Para cada cidade
        free(cidades[i].next_cidade);  // Free individual
        free(cidades[i].lig_id);       // Free individual
    }
    free(cidades);
    cidades = NULL;

}


#endif