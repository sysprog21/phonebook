#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#define HASH 1
#define MAX_LAST_NAME_SIZE 16
#define SIZE 3701

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

entry *findName(char lastname[], entry *e[]);
void append(char lastName[], entry *e[]);
void Free_List(entry *e);
unsigned int BKDRHash(char *str);
#endif
