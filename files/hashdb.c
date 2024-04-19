#include "hashdb.h"

typedef struct hash_struct{
    uint32_t hash;
    char name[50];
    uint32_t salary;
    struct hash_struct *next;
} hashRecord;

rwlock_t lock;
hashRecord *hashTable;
int hashTableSize;
int numAcquired;
int numReleased;
int numThreads;

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
    //  Printing command and hashing
    printf("INSERT, %s, %d\n", name, salary);
    uint32_t hashValue = jenkins_one_at_a_time_hash((const uint8_t *)name, strlen(name));
    
    //  Adding lock to prevent other threads from accessing bin
    rwlock_acquire_writelock(&lock);
    printf("WRITE LOCK ACQUIRED\n");
    numAcquired++;

    //  Adding to hash table
    //  First checks if the table exists
    if (hashTableSize == 0) {
        //  Creation of the hash table (linked list)
        hashTable = malloc(sizeof(hashRecord));
        hashTable->hash = hashValue;
        strcpy(hashTable->name, name);
        hashTable->salary = salary;
        hashTable->next = NULL;
        hashTableSize++;
    }
    else {
        hashRecord *current = hashTable;
        
        //  While loop to traverse the hash table (linked list)
        //  To reach the end
        while (current->next != NULL) {
            //  If the node's hash equals the hash value calculated
            //  It will story the information in that node
            if (current->hash == hashValue) {
                strcpy(current->name, name);
                current->salary = salary;
                rwlock_release_writelock(&lock);
                printf("WRITE LOCK RELEASED\n");
                numReleased++;
                return;
            }

            //  Traverse to next node
            current = current->next;
        }

        //  Creates new node and traverses to it
        //  Then stores data
        current->next = malloc(sizeof(hashRecord));
        current = current->next;
        current->hash = hashValue;
        strcpy(current->name, name);
        current->salary = salary;
        current->next = NULL;
        hashTableSize++;
    }

    rwlock_release_writelock(&lock);
    printf("WRITE LOCK RELEASED\n");
    numReleased++;
}

void delete(char *name){

}

void search(char *name){
    
}
void printTable(){
    
}

void readCommandFile() {

}