#include "hashdb.h"
#include "rwlocks.h" 

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
void insertHash(char *name, uint32_t salary){
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
            //  It will store the information in that node
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

void deleteHash(char *name){
    printf("DELETE,%s\n", name);
    uint32_t hashValue = jenkins_one_at_a_time_hash((const uint8_t *)name, strlen(name));

    rwlock_acquire_writelock(&lock);
    printf("WRITE LOCK ACQUIRED\n");
    numAcquired++;

    hashRecord *current = hashTable;

    if (current == NULL) {
        rwlock_release_writelock(&lock);
        printf("WRITE LOCK RELEASED\n");
        numReleased++;
        return;
    }

    if (current->hash == hashValue) {
        hashTable = current->next;
        free(current);
        hashTableSize--;
        rwlock_release_writelock(&lock);
        printf("WRITE LOCK RELEASED\n");
        numReleased++;
        return;
    }

    while (current->next != NULL) {
        if (current->next->hash == hashValue) {
            hashRecord *temp = current->next;
            current->next = current->next->next;
            free(temp);
            hashTableSize--;
            break;
        }

        current = current->next;
    }

    rwlock_release_writelock(&lock);
    printf("WRITE LOCK RELEASED\n");
    numReleased++;
}

void searchHash(char *name){
    // print to file
    uint32_t hashValue = jenkins_one_at_a_time(name, strlen(name));
    hashRecord* temp = hashTable;
    rwlock_acquire_readlock(&lock);

    // if the hash table is empty
    if(temp == NULL){
        // print file not found
        return;
    }

    // go through the hash table to find the record
    while(temp != NULL){
        
        if(temp->hash){
            //print the record
            // release read lock
            return;
        }
    }

    // release read lock
    // print file not found

}

void printTable(){
    rwlock_acquire_readlock(&lock);
    printf("READ LOCK ACQUIRED\n");
    numAcquired++; 

    hashRecord* temp = hashTable; 

    while(temp != NULL){
        printf("%u,%s,%u\n", temp->hash, temp->name, temp->salary);
        temp = temp->next;
    }

    rwlock_release_readlock(&lock);
    prinf("READ LOCK RELEASED\n");
    numReleased++;
}

// DELETEME
void readCommandFile() {

}