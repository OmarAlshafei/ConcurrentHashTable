#include "hashdb.h"

typedef struct hash_struct{
    uint32_t hash;
    char name[50];
    uint32_t salary;
    struct hash_struct *next;
} hashRecord; 

uint32_t jenkins_one_at_a_time(const uint8_t* key, size_t length){
    size_t i = 0;
    uint32_t hash = 0;
    while(i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

// the 3 functions for the hash table
void insert(char *name, uint32_t salary){
    printf("INSERT, %s, %d\n", name, salary);
    uint32_t hashValue = jenkins_one_at_a_time_hash((const uint8_t *)name, strlen(name));
    
}

void delete(char *name){

}

void search(char *name){
    
}
void printTable(){
    
}

void readCommandFile() {

}