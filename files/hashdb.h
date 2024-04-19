#ifndef __hashdb__h__
#define __hashdb__h__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// this the linked list struct used to store all the information
typedef struct hash_struct {
    uint32_t hash;
    char name[50];
    uint32_t salary;
    struct hash_struct *next;
} hashRecord;

void insertHash(char *name, uint32_t salary);
void searchHash(char *name);
void deleteHash(char *name);
void printTable();

#endif