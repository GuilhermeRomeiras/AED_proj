
#ifndef FILE_OPEN_H
#define FILE_OPEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h" // Para ter acesso às declarações

// funcao inicial que abre o ficheiro e armazena os dados em arrays que caracterizam, cada um, uma coluna do ficheiro .map
int read_file_map(FILE *file_map, int N, int L, int *cidade_part, int *cidade_cheg, int *automovel, int *time, int *cost, int *first, int *last, int *period, adj *cidades){

    // dentro da funcao read_file_map() logo após fscanf de N e L
    init_nodes(N, cidades);

    // Declarar arrays para cada coluna

    // Verificar se todos os malloc foram bem sucedidos
    if (!cidade_part || !cidade_cheg || !automovel || !time || !cost || !first || !last || !period){

        // Libertar memoria ja alocada
        free_vectors_map(cidade_part, cidade_cheg, automovel, time, cost, first, last, period);
        fclose(file_map);
        exit(0);
    }

    int n_con = 0; // Contador de conexoes lidas com sucesso
    
    for (int i = 0; i < L; i++){
        char str[10];
        int tmp_cp, tmp_cc, tmp_time, tmp_cost, tmp_first, tmp_last, tmp_p, tmp_aut;

        if (fscanf(file_map, "%d %d %10s %d %d %d %d %d",
                   &tmp_cp,
                   &tmp_cc,
                   str,
                   &tmp_time,
                   &tmp_cost,
                   &tmp_first,
                   &tmp_last,
                   &tmp_p) == 8){

            tmp_aut = Enum_str_to_int(str);

            if (tmp_aut == 0){
                continue;
            }

            cidade_part[i] = tmp_cp - 1;
            cidade_cheg[i] = tmp_cc - 1;
            automovel[i] = tmp_aut;
            time[i] = tmp_time;
            cost[i] = tmp_cost;
            first[i] = tmp_first;
            last[i] = tmp_last;
            period[i] = tmp_p;

        // dentro da funcao read_file_map() logo após guardar nos vetores as variaveis temporarias do fscanf (linha 89)
        nodes(tmp_cp-1, tmp_cc-1, i, cidades);
        }

        else{
            fclose(file_map);
            return 0;
        }
        n_con++;
    }   
    
    fclose(file_map);
    return 0;
}


#endif