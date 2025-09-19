#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"
#include "file_open.h"
#include "aux_functions.h"


int main(int argc, char *argv[]) {
    
    char *filename_map = argv[1];
    char *filename_quests = argv[2];


    read_file_map(filename_map);  
    read_file_quests(filename_quests);
    //print_arrays();

    if (argc != 3) {
       fprintf(stderr, "argument count is wrong\n");
       exit(0);
    }
    

    // Libertar toda a memoria dos arrays no fim da execucao do programa
    free_vectors_map();
    free_vectors_quests();

    return 0;
}