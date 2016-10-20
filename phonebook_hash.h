#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#define HASH 1
#define MAX_LAST_NAME_SIZE 16
#define SIZE 9971

typedef struct __PHONE_BOOK_DETAIL {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail;



typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *pDetail;
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;


typedef struct __HASH_TABLE {
    entry **list ;
} hashTable;



entry *findName(char lastname[], hashTable *ht);
void append(char lastName[], hashTable *ht);
void freeHashList(hashTable * ht);
hashTable *hashTableInitial(void);
unsigned int BKDRHash(char *str);
#endif
