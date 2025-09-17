



int read_file_quests(const char* filename){ 
    
    FILE *file_map = fopen(filename, "r");
    char *buffer;;

    if (!file_map) {
        perror(filename);
        return 0;
    }

    fgets(buffer, strlen(buffer), file_map);
    fprintf("argument received: %s\n", buffer);
    printf("File opened successfully!\n");
    return 0;
}