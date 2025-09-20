#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include "header.h"

// Funcao auxiliar para imprimir os dados dos arrays
void print_arrays(void) {

    printf("\n=== Array Data ===\n");
    for (int i = 0; i < L; i++) {
        const char *mode_str = Enum_int_to_str(automovel[i]);

        printf("Connection %d:\n", i+1);
        printf("  cidade_part: %d\n", cidade_part[i]);
        printf("  cidade_cheg: %d\n", cidade_cheg[i]);
        printf("  automovel: %s (%d)\n", mode_str, automovel[i]);
        printf("  cost: %d\n", cost[i]);
        printf("  time: %d\n", time[i]);
        printf("  first: %d\n", first[i]);
        printf("  last: %d\n", last[i]);
        printf("  period: %d\n\n", period[i]);
    }

}



// Funcao que transforma a string do ficheiro em inteiro para melhor manipulacao
int Enum_str_to_int(const char *str, int num_con_err){
    
    if (strcmp(str, "aviao") == 0) return AVIAO;
    else if (strcmp(str, "comboio") == 0) return COMBOIO;
    else if (strcmp(str, "barco") == 0) return BARCO;
    else if (strcmp(str, "autocarro") == 0) return AUTOCARRO;
    else {
        printf("Invalid transportation in connection %d\n", num_con_err+1);
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
void free_vectors_map(void) {

    free(cidade_part);
        cidade_part = NULL;

    free(cidade_cheg); 
        cidade_cheg = NULL; 

    free(automovel);
       automovel = NULL; 

    free(cost);
        cost = NULL; 

    free(time);
        time = NULL;   

    free(first);
       first = NULL;

    free(last);
        last = NULL; 

    free(period);
        period = NULL; 

}



// free dos dados armazenados do ficheiro quests
void free_vectors_quests() {

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


#endif