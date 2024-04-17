#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "common_threads.h"
#include "rwlocks.h"


// this the linked list struct used to store all the information
typedef struct hash_struct {
    uint32_t hash;
    char name[50];
    uint32_t salary;
    struct hash_struct *next;
} hashRecord;

void insert(char *name, uint32_t salary);
void search();
void delete();

