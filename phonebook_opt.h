#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define TABLE_SIZE 127

/* 
*******************************************************************
TODO: After modifying the original version, uncomment the following
 * line to set OPT properly 
******************************************************************
*/

//#define __SMALL_STRUCT__ 1
//#define __BST__ 1
#define __HASH__ 1


/*
**************************
Orignial Structure
**************************
*/
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
}detail;
/////////////////////////////

/*
*****************************
Small Structure
*****************************
*/
typedef struct __LAST_NAME{
	char lastName[ MAX_LAST_NAME_SIZE];
	detail *dNext;
	struct __LAST_NAME *pNext;
}entry;
/////////////////////////////

/*
*******************************
Node of Binary Search Tree
*******************************
*/

typedef struct _PHONE_BOOK_BST {
    struct __LAST_NAME *data;
    struct _PHONE_BOOK_BST *left;
    struct _PHONE_BOOK_BST *right;
}BST;


/*
*******************************
Hash Table and Hash Item
*******************************
*/
typedef struct _HASH_ITEM_{
	char lastName[ MAX_LAST_NAME_SIZE ];
	int key;
	struct _HASH_ITEM_ *next;
}HashItem;


typedef struct _HASH_TABLE_{
	int len;
	HashItem *next;
}HashTable;
/////////////////////////////////


//original version
entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

//BST version
BST *BSTfindName(char lastname[], BST *root);
BST *sortedListToBSTRecur(entry** node, int len);
void freeBST(BST *root);

//hash version
HashItem *hash_append(HashTable *slutPtr, char *str, int key);
HashItem *hash_findName(HashTable *table, int id, char lastname[]);
int hash_func(char *str);
void init_hash_table(HashTable *table);
void free_hash_table(HashTable *table);


#endif
