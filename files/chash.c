#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include "common.h"
#include "common_threads.h"
#include "hashdb.h"

extern void insertHash(char *name, uint32_t salary);
extern void searchHash(char *name);
extern void deleteHash(char *name);
extern void printTable();

int main()
{
    // read commands from file and parses each command

    // open command file
    FILE *file = fopen("commands.txt", "r");
    if(file == NULL){
        printf("Failed to open file\n");
        return 1;
    }

    // read each line, get command, and parse the command
    char line[100];
    char command[10];
    char param1[10];
    uint32_t param2;
    int numThreads;

    while (fgets(line, sizeof(line), file) != NULL){
        // Remove the newline character from the line
        line[strcspn(line, "\n")] = '\0';
                                                                                
        // Parse the command
        sscanf(line, "%9[^,]", command);

        if (strcmp(command, "threads") == 0) {
            // Parse thread count and additional parameter
            sscanf(line, "threads,%d,%d", &numThreads, &param2);
            //printf("Threads: %d, %d\n", numThreads, param2);
        } else if (strcmp(command, "insert") == 0) {
            sscanf(line, "insert,%[^,],%d", param1, &param2);
            //printf("Insert: %s %d\n", param1, param2);
            insertHash(param1, param2);
        } else if (strcmp(command, "search") == 0) {
            sscanf(line, "search,%[^,]", param1);
            //printf("Search: %s\n", param1);
            searchHash(param1);
        } else if (strcmp(command, "delete") == 0) {
            sscanf(line, "delete,%[^,]", param1);
            //printf("Delete: %s\n", param1);
            deleteHash(param1);
        } else if (strcmp(command, "print") == 0) {
            printTable();
        }
    }

    return 0;
}