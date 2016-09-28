#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_hash.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *e[])
{
    /* TODO: implement */
    entry *tmp;
    unsigned int n = BKDRHash(lastname);
    /*judge if e[n] has value*/
    if(e[n]->pNext) {
        tmp = e[n]->pNext;
    } else return NULL;
    /*findname*/
    while(tmp) {
        if (strcasecmp(lastname, tmp->lastName) == 0)
            return tmp;
        tmp = tmp->pNext;
    }
    return NULL;
}

void append(char lastName[], entry *e[])
{
    entry *tmp;
    unsigned int n=BKDRHash(lastName);
    /*if e[n] has no data*/
    if (e[n]->pNext== NULL) tmp = e[n];
    else tmp = e[n]->pNext;
    tmp->pNext = (entry *) malloc(sizeof(entry));
    tmp = tmp->pNext;
    strcpy(tmp->lastName, lastName);
    tmp->pNext = NULL;
    e[n]=tmp;
}

unsigned int BKDRHash(char lastName[])
{
    unsigned int seed=31;
    unsigned int hash=0;
    int i=0;
    while(i<strlen(lastName)) {
        hash = hash * seed + lastName[i++];

    }

    return hash %= SIZE;
}

void Free_List(entry *e)
{
    entry *tmp;
    while(e) {
        tmp = e->pNext;
        free(e);
        e = tmp;
    }
}

