#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <sys/types.h>
#include <unistd.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"
#define GIVEN_NAME "zyxel"

//function prototype
static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int list_len=0;
    char buff[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double append_time, find_time;

	//getpid
//	printf("pid: %d\n", getpid() );
	
    // check file opening
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#if defined(__HASH__)
	HashTable *hashArray = (HashTable *)malloc( sizeof(HashTable) * TABLE_SIZE );
	init_hash_table( hashArray );
	printf("size of hash item : %lu bytes\n", sizeof(HashItem));
#else
    // build the head entry
	//printf("pid: %d\n", getpid() );
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
	#if defined(__BST__)
	printf("size of tree node : %lu bytes\n", sizeof(BST));
	#endif
#endif

#if defined(__HASH__)
    __builtin___clear_cache((char *) hashArray, (char *) hashArray + sizeof(TABLE_SIZE));
#elif defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
	
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(buff, sizeof(buff), fp)) {
        buff[ strlen(buff)-1 ] = '\0';
#if defined(__HASH__)
		int key = hash_func(buff);
		hash_append(hashArray, buff, key);
#else
        e = append(buff, e);
#endif
		list_len++;
    }
    /* close file as soon as possible */
    fclose(fp);



#if defined(__BST__)
	e = pHead;
	BST *root = sortedListToBSTRecur( &e, list_len);
#endif

    clock_gettime(CLOCK_REALTIME, &end);
    append_time = diff_in_second(start, end);



    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = GIVEN_NAME;


/*#if defined(__BST__)
	assert(BSTfindName(input, root) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(BSTfindName(input, root)->data, "zyxel"));
#else
    assert(findName(input, e) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, e)->lastName, "zyxel"));
#endif
*/


/*#if defined(__SMALL_STRUCT__)&defined(__GNUC__)
	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));

	clock_gettime(CLOCK_REALTIME, &start);
	findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);
	
    find_time = diff_in_second(start, end);
*/

#if defined(__BST__)&defined(__GNUC__)
	__builtin___clear_cache((char *) root, (char *) root + sizeof(BST));
	e = pHead;
	clock_gettime(CLOCK_REALTIME, &start);
	BSTfindName(input, root);
    clock_gettime(CLOCK_REALTIME, &end);

    find_time = diff_in_second(start, end);
	freeBST(root);
#elif defined(__HASH__)&defined(__GNUC__)
    __builtin___clear_cache((char *) hashArray, (char *) hashArray + sizeof(TABLE_SIZE));

	clock_gettime(CLOCK_REALTIME, &start);
	hash_findName(hashArray, hash_func(input)%TABLE_SIZE, input );
    clock_gettime(CLOCK_REALTIME, &end);

	find_time = diff_in_second(start, end);
#elif defined(__GNUC__)
	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
	e = pHead;
	clock_gettime(CLOCK_REALTIME, &start);
	findName(input, e);
    clock_gettime(CLOCK_REALTIME, &end);

	find_time = diff_in_second(start, end);
#endif



    FILE *output;
#if defined(__SMALL_STRUCT__)
    output = fopen("small_struct.txt", "a");
#elif defined(__BST__)
	output = fopen("bst.txt", "a");
#elif defined(__HASH__)
	output = fopen("hash.txt", "a");
#else
	output = fopen("orig.txt", "a");
#endif
	fprintf(output, "append() findName() %lf %lf\n", append_time, find_time);
    fclose(output);
    printf("execution time of append() : %lf sec\n", append_time);
    printf("execution time of findName() : %lf sec\n", find_time);

	
#if defined(__HASH__)
	free_hash_table(hashArray);
#else
	while((e = pHead)){
		pHead = pHead->pNext;
		free(e);
	}
#endif

    return 0;
}

