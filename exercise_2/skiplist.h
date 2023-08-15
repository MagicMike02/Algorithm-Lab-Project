#define MAX_HEIGHT 30

#include <stdio.h>
#include <stdlib.h>

typedef struct _Skiplist Skiplist;
typedef struct _Node Node;

struct _Skiplist{
    Node *head;
    unsigned int max_level;
    int (*compare)(void*,void*);
};

struct _Node{
    Node **next;
    unsigned int size;
    void* item;
};

// Creates the skip list and returns the head
Skiplist * skipList_create(int (*compare)(void*, void *));
void insertSkiplist(Skiplist * List ,void * I);  //funzione dove caricare il dizionario
void *searchSkipList(Skiplist *list, void *I); //funzione dove cercare le parole da corregge non presenti in skiplist dove è stato caricato il dizionario
void skiplist_free(Skiplist *list);