#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"


/* FILL YOUR OWN IMPLEMENTATION HERE! */


/*
**************************
Original
**************************
*/

entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

//I will use the original append to create a linked-list, because I will transform the sorted-linked-list to a bst
entry *append(char lastName[], entry *e)
{
	/* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
	e->dNext = NULL;

    return e;
}
/////////////////////////////////////

/*
******************************
Binary Search Tree
******************************
*/

//findName in bst version
BST *BSTfindName(char lastname[], BST *root)
{

    /* TODO: implement */
	//bst version
	int buf;
	while( root != NULL ){
		if( !( buf = strcasecmp(lastname, (root->data)->lastName) ) ){
			return root;
		}
		else{
			return BSTfindName( lastname, buf>0 ? root->right : root->left );//
		}
	}
    return NULL;
}

//Tranform the sorted linked-list to bst
BST *sortedListToBSTRecur(entry** node, int len)
{
    if(!len)
		return NULL;

    //build left subtree recursively
    BST *left = sortedListToBSTRecur(node, len>>1);

    //create root
    BST *root = (BST *) malloc( sizeof(BST) );
    root -> data = (entry *)malloc(sizeof(entry));
    strcpy((root->data)->lastName, (*node)->lastName);
    root->left = left;

    //move the node to the next in this recursion step
	//when this step returns, the previous recursion step will get the next node
    *node = (*node)->pNext;

	//build right node
    root->right = sortedListToBSTRecur(node, len-(len>>1)-1);

    return root;
}

void freeBST( BST *root ){
	if(!root)
		return;
	freeBST(root->left);
	freeBST(root->right);
	free(root);
}

///////////////////////////////////////


/*
******************************
Hash Table version
******************************
*/

//append hash item
HashItem *hash_append(HashTable *slutPtr, char *str, int key){
	int id = key % TABLE_SIZE;
	HashItem *tmp = slutPtr[id].next;
	HashItem *item = (HashItem *)malloc( sizeof(HashItem) );
	strcpy(item->lastName, str);
	item->key = key;
	
	slutPtr[id].next = item;
	item->next = tmp;
	return item;
}

//get hash key
int hash_func(char *str){
	int key=0;
	while( *str )
		key += (*str++);
	return key;
}

//initialize hash table
void init_hash_table(HashTable *table){
	for(int i=0; i<TABLE_SIZE; i++){
		table[i].len=0;
		table[i].next=NULL;
	}
}

//free hash table
void free_hash_table(HashTable *table){
	HashItem *head, *curr;
	for(int i=0; i<TABLE_SIZE; i++){
		head = table[i].next;
		while( (curr=head) != NULL ){
			head=head->next;
			free(curr);
		}
	}
	free(table);
}

//findName in hash version
HashItem *hash_findName(HashTable *table, int id, char lastname[]){
	HashItem *item = table[id].next;
	int ans;
	while( item ){
		//printf("???\n\n");
		if( (ans = strcasecmp(item->lastName, lastname))==0 )
			return item;
		else if(ans>0)
			return NULL;
		item = item->next;
	}
	return NULL;
}
////////////////////////////////////////
