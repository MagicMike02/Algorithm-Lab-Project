#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 30 // MAX Number of "Express line" a node can have

typedef struct _SkipList SkipList;
typedef struct _Node Node;

// Defining generic pointer to a compare function
typedef int (*compareFunction)(void*, void*);

struct _SkipList {
  Node* head;
  unsigned int max_level;
  int (*compare)(void*, void*);
};

struct _Node {
  Node **next;
  unsigned int size;
  void *item;
};

int randomLevel();

Node* createNode(void* item, int level);

SkipList* newSkipList(compareFunction cmpFun);

void SkipList_print(SkipList *list);

void deleteSkipList(SkipList* l);

void insertSkipList(SkipList* list, void* item);

void* searchSkipList(SkipList* list, void* item);

void readFile1(SkipList* skl, char* filename);

void checkPhrase(SkipList* skl, char* filename);

//Compare strings
int compareField1(void* item1, void* item2);
//Compare integers
int compareField2(void* item1, void* item2);
//Compare decimals
int compareField3(void* item1, void* item2);

