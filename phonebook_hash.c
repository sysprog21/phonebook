#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], hashTable *ht)
{
    /* TODO: implement */
    entry *tmp = NULL;
    unsigned int hash = BKDRHash(lastname);
    /*findname*/
    while(ht->list[hash]) {
        tmp = ht->list[hash];
        if (strcasecmp(lastname, tmp->lastName) == 0)
            return tmp;
        tmp = tmp->pNext;
    }
    return NULL;
}

void append(char lastName[], hashTable *ht)
{
    entry *tmp;
    unsigned int hash = BKDRHash(lastName);
    tmp = (entry *) malloc(sizeof(entry));

    tmp->pNext = ht->list[hash];
    strcpy(tmp->lastName, lastName);
    ht->list[hash]=tmp;
}

hashTable *hashTableInitial()
{
    hashTable *ht = NULL;
    ht = (hashTable *)malloc(sizeof(hashTable));
    ht->list =(entry **)malloc(sizeof(entry *)*SIZE);
    int i =0;
    while(i<SIZE) {
        ht->list[i] =NULL;
        i++;
    }

    return ht;
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed=31;
    unsigned int hash=0;
    int i = 0;
    while(i<strlen(str)) {
        hash = hash * seed + *str++ ;
    }

    return hash % SIZE;
}

void freeHashList(hashTable *ht)
{
    for(int i=0; i<SIZE; i++) {
        entry *tmp = NULL;
        while(ht->list[i]) {
            tmp = (ht->list[i])->pNext;
            free(ht->list[i]);
            ht->list[i] = tmp;
        }
    }
    free(ht);
}

