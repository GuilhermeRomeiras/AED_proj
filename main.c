#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"
#include "task_functions.h"
#include "file_open.h"
#include "aux_functions"



enum {invalid_transport, COMBOIO, BARCO, AUTOCARRO, AVIAO};
int N, L;


int main(int argc, char *argv[]) {

    char *filename_map = argv[1];
    char *filename_quests = argv[2];

    read_file_map(filename_map);  
    read_file_quests(filename_quests);

    if (argc != 3) {
       fprintf(stderr, "argument count is wrong\n");
       return EXIT_FAILURE;
    }
    

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors();

    return 0;

}
